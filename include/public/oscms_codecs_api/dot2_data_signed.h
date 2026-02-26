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

#ifndef OSCMS_DOT2_DATA_SIGNED_H
#define OSCMS_DOT2_DATA_SIGNED_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_certificate.h"
#include "oscms_codecs_api/oscms_signature.h"
#include "oscms_codecs_api/so_export.h"

    /**
     * @file dot2_data_signed.h
     */
    /**
     * A 1609Dot2Data-Signed is never used in it's bare form. Rather it is usually
     * used in the definition of a higher level SPDU, such as CertificateManagementInfoStatusSpdu.
     *
     * This type field allows the concrete implementation to determine the type of the higher level SPDU or PDU
     * and apply the appropriate constraints and checking, using internal representations of the higher level
     * construct.
     */
    typedef enum OscmsDot2DataSignedType
    {
        OSCMS_DOT2_DATA_SIGNED_TYPE_UNKNOWN                                 = 0,
        OSCMS_DOT2_DATA_SIGNED_TYPE_CERTIFICATE_MANAGEMENT_INFO_STATUS_SPDU = 1,
        OSCMS_DOT2_DATA_SIGNED_TYPE_CTL_SIGNATURE_SPDU                      = 2,
        OSCMS_DOT2_DATA_SIGNED_TYPE_ECA_EE_CERT_RESPONSE_SPDU               = 3,
        OSCMS_DOT2_DATA_SIGNED_TYPE_EE_ECA_CERT_REQUEST_SPDU                = 4,
        OSCMS_DOT2_DATA_SIGNED_TYPE_RA_EE_CERT_ACK_SPDU                     = 5,
        OSCMS_DOT2_DATA_SIGNED_TYPE_RA_EE_ENROLLMENT_CERT_ACK_SPDU          = 6,
        OSCMS_DOT2_DATA_SIGNED_TYPE_DOT_DATA_SIGNED_ENCRYPTED_SPDU          = 7,
        OSCMS_DOT2_DATA_SIGNED_TYPE_ACA_RA_CERT_RESPONSE_SPDU               = 8,
        OSCMS_DOT2_DATA_SIGNED_TYPE_RA_EE_DOWNLOAD_REQUEST_SPDU             = 9,
        OSCMS_DOT2_DATA_SIGNED_TYPE_RA_EE_CERT_INFO_SPDU                    = 10,
    } OscmsDot2DataSignedType;

    // Arguments for encoding an Ieee1609Dot2Data_Signeds
    //
    // Note we assume sha256 is used for the hash algorithm
    typedef struct OscmsDot2DataSignedArgs
    {
        OscmsDot2DataSignedType enclosing_type;

        OscmsOctetBuffer payload; // Unencrypted data that has been signed
        OscmsPsid payload_psid;   // PSID associated with the data
        OscmsSignature signature; // Signature for the data

        // This is already a COER-encoded Certificate_t which is used to complete the
        // signer identifier field.
        OscmsOctetBuffer signer_certificate;
    } OscmsDot2DataSignedArgs;

    // Decoded Ieee1609Dot2Data_Signed
    //
    // See IEEE 1609.2-2022, Section 6.3.4
    typedef struct OscmsSignedData
    {
        OscmsPsid payload_psid;              // PSID associated with the data
        OscmsOctetBuffer payload;            // Unencrypted data that was signed
        OscmsSignature signature;            // Signature for the data
        OscmsCertificate signer_certificate; // Certificate of the signer
    } OscmsSignedData;

    /**
     * @brief Encode an Ieee1609Dot2Daa-Signed SPDU
     *
     * See IEEE 1609.2.1-2022, Section 7.5.4
     *
     *
     * @param[in] args A pointer to the input arguments
     * @param[out] buffer Pointer to the buffer where the encoded DataSigned will be stored
     *
     * The caller is responsible for freeing the memory allocated for the output buffer
     *
     * An Ieee1609Dot2Data_Signed SPDU is defined in the specification as a parameterized type representing
     * a higher level SPDU, such as CertificateManagementInfoStatusSpdu. This is the actual type which must be
     * used for the encoding and constraint checking. If a type of "UNKNOWN" is provided, the encoding should use
     * the generic Ieee1609Dot2Data_Signed encoding.
     *
     * @return 0 on success, and the provided `buffer` will contain the encoded DataSigned and length.
     */

    SO_EXPORT int oscms_encode_dot2_data_signed(const OscmsDot2DataSignedArgs *args, OscmsOctetBuffer *buffer);

    /**
     * @brief Decode an Ieee1609Dot2Daa-Signed SPDU
     *
     * @param[in] buffer A pointer to the input buffer
     * @param[in] type The type of the enclosing SPDU
     * @param[out] signed_data Pointer to the decoded DataSigned
     *
     * An Ieee1609Dot2Data_Signed SPDU is defined in the specification as a parameterized type representing
     * a higher level SPDU, such as CertificateManagementInfoStatusSpdu. This is the actual type which must be
     * used for the encoding and constraint checking. If a type of "UNKNOWN" is provided, the encoding should use
     * the generic Ieee1609Dot2Data_Signed encoding.
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_decode_dot2_data_signed(
        const OscmsOctetBuffer *buffer, OscmsDot2DataSignedType type, OscmsSignedData *signed_data);

    /**
     * @brief Free memory allocated for an OscmsSignedData
     *
     * @param[in] signed_data The OscmsSignedData to free
     *
     * Does NOT free the OscmsSignedData itself
     */
    SO_EXPORT void oscms_empty_signed_data(OscmsSignedData *signed_data);

    /**
     * @brief Free memory allocated for an OscmsSignedData
     *
     * @param[in] data The OscmsSignedData to free
     *
     * Empties the OscmsSignedData, then frees the OscmsSignedData itself
     */

    SO_EXPORT void oscms_free_signed_data(OscmsSignedData *data);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // OSCMS_DOT2_DATA_SIGNED_H
