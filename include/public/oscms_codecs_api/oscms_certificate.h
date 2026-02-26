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

#ifndef OSCMS_CERTIFICATE_H
#define OSCMS_CERTIFICATE_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_sequence.h"
#include "oscms_codecs_api/oscms_signature.h"
#include "oscms_codecs_api/oscms_tbs_certificate.h"
#include "oscms_codecs_api/so_export.h"

    typedef enum OscmsIssuerIdentifierType
    {
        OSCMS_ISSUER_IDENTIFIER_SHA256_AND_DIGEST = 1,
        OSCMS_ISSUER_IDENTIFIER_SELF              = 2,
        OSCMS_ISSUER_IDENTIFIER_SHA384_AND_DIGEST = 3,
        OSCMS_ISSUER_IDENTIFIER_SM3_AND_DIGEST    = 4,
    } OscmsIssuerIdentifierType;

    typedef struct OscmsCertificate
    {
        OscmsCertificateType type;

        OscmsIssuerIdentifierType issuer_identifier_type;
        union
        {
            OscmsHashedId8 hash;               // For type sha256 and sha384
            OscmsHashAlgorithm hash_algorithm; // For type self
        } issuer_identifier;

        OscmsTbsCertificate tbs_certificate;
        OscmsSignature *signature; // OPTIONAL

        OscmsSequence allocations;
    } OscmsCertificate;

    /**
     * @brief Decode a COER-encoded Certificate_t
     *
     * See IEEE 1609.2-2022 specification 6.4.2
     *
     * @param[in] encoded_certificate A pointer to the input COER-encoded Certificate_t
     * @param[out] decoded_certificate A pointer to the output decoded Certificate_t
     *
     * @return 0 on success, non-zero on failure
     */
    SO_EXPORT int oscms_decode_certificate(
        const OscmsOctetBuffer *encoded_certificate, OscmsCertificate *decoded_certificate);

    /**
     * @brief Encode a COER-encoded Certificate_t
     *
     * See IEEE 1609.2-2022 specification 6.4.2
     *
     * @param[in] certificate A pointer to the API representation to be encoded
     * @param[out] encoded_certificate A pointer to an OscmsOctetBuffer to hold the encoded COER-encoded Certificate_t
     *
     * `oscms_empty_octet_buffer()` must be called on the output buffer
     *
     * @return 0 on success, non-zero on failure
     */
    SO_EXPORT int oscms_encode_certificate(const OscmsCertificate *certificate, OscmsOctetBuffer *encoded_certificate);

    /**
     * @brief Encode the ToBeSignedCertificate part of a Certificate
     *
     * See IEEE 1609.2-2022 specification 6.4.4
     *
     * @param[in] certificate A pointer to the API representation to be encoded
     * @param[out] encoded_certificate A pointer to an OscmsOctetBuffer to hold the encoded COER-encoded
     * ToBeSignedCertificate
     *
     * `oscms_empty_octet_buffer()` must be called on the output buffer
     *
     * @return 0 on success, non-zero on failure
     */
    SO_EXPORT int oscms_encode_tbs_certificate(
        const OscmsCertificate *certificate, OscmsOctetBuffer *encoded_certificate);

    /**
     * Convert an internal representation of a Certificate to the API's representation.
     *
     * @param[in] internal_certificate_void A pointer to the internal representation
     * @param[out] decoded_certificate A pointer to the output decoded Certificate_t
     *
     * @return 0 on success, non-zero on failure
     */
    int oscms_certificate_from_internal(const void *internal_certificate_void, OscmsCertificate *decoded_certificate);

    /**
     * Convert an API representation of a Certificate to the internal representation.
     *
     * @param[in] oscms_certificate A pointer to the API representation
     * @param[out] internal_certificate A pointer to the internal representation
     *
     * @return 0 on success, non-zero on failure
     */
    int oscms_internal_from_certificate(const OscmsCertificate *oscms_certificate, void *internal_certificate);

    /**
     * Clear the contents of the provided OscmsCertificate structure, releasing all allocated memory
     *
     * Does NOT free the OscmsCertificate structure itself
     *
     * @param certificate The OscmsCertificate to clear
     *
     * @return void
     */
    SO_EXPORT void oscms_empty_certificate(OscmsCertificate *certificate);

    /**
     * Clear the contents of the provided OscmsCertificate structure, releasing all allocated memory and the
     * OscmsCertificate structure itself
     *
     * @param certificate The OscmsCertificate to clear
     *
     * @return void
     */
    SO_EXPORT void oscms_free_certificate(OscmsCertificate *certificate);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // OSCMS_CERTIFICATE_H
