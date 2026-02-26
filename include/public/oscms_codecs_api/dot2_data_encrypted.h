// Copyright (c) 2025 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef OSCMS_DOT2_DATA_ENCRYPTED_H
#define OSCMS_DOT2_DATA_ENCRYPTED_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_sequence.h"
#include "oscms_codecs_api/so_export.h"

    /**
     * @file dot2_data_encrypted.h
     *
     * @brief Definition of types and API functions for the Ieee1609Dot2Data-Encrypted entity
     *
     * See Ieee1609.2.1-2022 Section 7.5.2
     *
     */

    // Symmetric Ciphertext - See Ieee1609.2-2022 Section 6.3.49
    typedef enum OscmsSymmCiphertextType
    {
        OSCMS_SYMMETRIC_CIPHERTEXT_UNKNOWN = 0,
        OSCMS_SYMMETRIC_CIPHERTEXT_AES128  = 1,
        OSCMS_SYMMETRIC_CIPHERTEXT_SM4_CCM = 2,
    } OscmsSymmCiphertextType;

    typedef struct OscmsSymmetricCiphertext
    {
        OscmsSymmCiphertextType type;
        OscmsOctetBuffer cipher_text; // Encrypted payload
        OscmsOctetBuffer nonce;
    } OscmsSymmetricCiphertext;

    // OscmsEncryptedDataEncryptionKey (EDEK)
    // See Ieee1609.2-2022 Section 6.3.46
    typedef enum OscmsEdekType
    {
        OSCMS_EDEK_TYPE_UNKNOWN        = 0,
        OSCMS_EDEK_TYPE_NIST_P256      = 1,
        OSCMS_EDEK_TYPE_BRAINPOOL_P256 = 2,
        OSCMS_EDEK_TYPE_SM2            = 3
    } OscmsEdekType;

    typedef struct OscmsEncryptedDataEncryptionKey
    {
        OscmsEdekType type;
        OscmsEccCurvePoint public_key;  // "v" value from spec - Curve type should match EDEK type.
        OscmsOctetBuffer symmetric_key; // "c" value from spec
        OscmsOctetBuffer tag;           // "t" value from spec

    } OscmsEncryptedDataEncryptionKey;

    // Recipient information related structures

    // The RecipientInfo object itself.
    // See Ieee1609.2-2022 Section 6.3.42
    typedef enum OscmsRecipientInfoType
    {
        OSCMS_RECIPIENT_INFO_TYPE_UNKNOWN     = 0,
        OSCMS_RECIPIENT_INFO_TYPE_PSK         = 1,
        OSCMS_RECIPIENT_INFO_TYPE_SYMMETRIC   = 2,
        OSCMS_RECIPIENT_INFO_TYPE_CERTIFICATE = 3,
        OSCMS_RECIPIENT_INFO_TYPE_SIGNED      = 4,
        OSCMS_RECIPIENT_INFO_TYPE_REK         = 5,
    } OscmsRecipientInfoType;

    typedef struct OscmsRecipientInfo
    {
        OscmsRecipientInfoType type;
        union
        {
            // OSCMS_RECIPIENT_INFO_TYPE_PSK
            OscmsHashedId8 psk;

            // OSCMS_RECIPIENT_INFO_TYPE_SYMMETRIC
            struct
            {
                OscmsHashedId8 recipient_id;
                OscmsSymmetricCiphertext encryption_key;
            } symmetric;

            // OSCMS_RECIPIENT_INFO_TYPE_CERTIFICATE
            // OSCMS_RECIPIENT_INFO_TYPE_SIGNED
            // OSCMS_RECIPIENT_INFO_TYPE_REK
            struct
            {
                OscmsHashedId8 recipient_id;
                OscmsEncryptedDataEncryptionKey encryption_key;
            } public_key;

        } value;

    } OscmsRecipientInfo;

    /**
     * A 1609Dot2Data-Encrypted is never used in it's bare form. Rather it is usually
     * used in the definition of a higher level SPDU, such as CertificateManagementInfoStatusSpdu.
     *
     * This type  allows the concrete implementation to determine the type of the higher level SPDU or PDU
     * and apply the appropriate constraints and checking, using internal representations of the higher level construct.
     */

    typedef enum OscmsDot2DataEncryptedType
    {
        OSCMS_DOT2_DATA_ENCRYPTED_TYPE_UNKNOWN,
        OSCMS_DOT2_DATA_ENCRYPTED_TYPE_EE_RA_CERT_REQUEST_SPDU,
        OSCMS_DOT2_DATA_ENCRYPTED_TYPE_EE_RA_DOWNLOAD_REQUEST_SPDU,
        OSCMS_DOT2_DATA_ENCRYPTED_TYPE_EE_RA_SUCCESSOR_ENROLLMENT_CERT_REQUEST_SPDU,
        OSCMS_DOT2_DATA_ENCRYPTED_TYPE_ACA_EE_CERT_RESPONSE_CUBK_SPDU,
    } OscmsDot2DataEncryptedType;

    typedef struct OscmsDot2DataEncrypted
    {
        OscmsDot2DataEncryptedType enclosing_type;
        OscmsRecipientInfo *recipients;
        size_t recipient_count;

        OscmsSymmetricCiphertext ciphertext;

        // This field does not form part of the standard.
        //
        // One of these structures may contain a large number of dynamically allcoated buffers. It is strongly
        // recommended that concrete implementations of the decoding function use this sequence to track all such
        // buffers.
        //
        // Clients initializing a structure  also free to use  this.
        //
        // The memory used can then be freed using the `oscms_empty_sequence` function.
        //
        OscmsSequence allocations;
    } OscmsDot2DataEncrypted;

    /**
     * @brief Decode the Ieee1609Dot2Data-Encrypted
     *
     * Extract the encrypted payload and recipient information from a COER encoded Ieee1609Dot2Data-Encrypted
     * structure.
     *
     * Specifying the enclosing type allows the implementations to check for specific constraints on the higher level
     * SPDU or PDU
     *
     * @param[in] encoded The COER encoded Ieee1609Dot2Data-Encrypted
     * @param[in] enclosing_type The type of the enclosing SPDU or PDU
     * @param[out] dot2_data_encrypted The decoded Ieee1609Dot2Data-Encrypted
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_decode_dot2_data_encrypted(
        const OscmsOctetBuffer *encoded,
        OscmsDot2DataEncryptedType enclosing_type,
        OscmsDot2DataEncrypted *dot2_data_encrypted);

    /**
     * @brief Encode the Ieee1609Dot2Data-Encrypted
     *
     * Encode the OScmsDot2DataEncrypted into a COER encoded Ieee1609Dot2Data-Encrypted
     *
     * @param[in] dot2_data_encrypted The Ieee1609Dot2Data-Encrypted to encode
     * @param[out] encoded The COER encoded Ieee1609Dot2Data-Encrypted
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_encode_dot2_data_encrypted(
        const OscmsDot2DataEncrypted *dot2_data_encrypted, OscmsOctetBuffer *encoded);

    /**
     * @brief Free all memory allocated for the OscmsDot2DataEncrypted
     *
     * Releases all memory allocated in building the OscmsDot2DataEncrypted, but not the OscmsSequence instance itself.
     *
     * @param[in] dot2_data_encrypted The OscmsDot2DataEncrypted to free
     */
    SO_EXPORT void oscms_empty_dot2_data_encrypted(OscmsDot2DataEncrypted *dot2_data_encrypted);

    /**
     * @brief Free all memory allocated for the OscmsDot2DataEncrypted
     *
     * Releases all memory allocated in building the OscmsDot2DataEncrypted, as well as the OscmsDot2DataEncrypted
     * instance itself.
     *
     * @param[in] dot2_data_encrypted The OscmsDot2DataEncrypted to free
     */
    SO_EXPORT void oscms_free_dot2_data_encrypted(OscmsDot2DataEncrypted *dot2_data_encrypted);
#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_DOT2_DATA_ENCRYPTED_H
