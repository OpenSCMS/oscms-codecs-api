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

#ifndef OSCMS_SIGNED_CERT_REQUEST_H
#define OSCMS_SIGNED_CERT_REQUEST_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_certificate.h"
#include "oscms_codecs_api/oscms_ee_eca_cert_request.h"
#include "oscms_codecs_api/oscms_ee_ra_cert_request.h"
#include "oscms_codecs_api/oscms_sequence.h"
#include "oscms_codecs_api/oscms_signature.h"
#include "oscms_codecs_api/so_export.h"

    // IEEE 1609.2-2022 Section 6.3.31
    typedef enum OscmsSignerIdentifierType
    {
        OSCMS_SIGNER_IDENTIFIER_TYPE_NONE         = 0,
        OSCMS_SIGNER_IDENTIFIER_TYPE_DIGEST       = 1,
        OSCMS_SIGNER_IDENTIFIER_TYPE_CERTIFICATES = 2,
        OSCMS_SIGNER_IDENTIFIER_TYPE_SELF         = 3,
    } OscmsSignerIdentifierType;

    typedef struct OscmsSignerIdentifier
    {
        OscmsSignerIdentifierType type;
        union
        {
            OscmsHashedId8 digest;
            struct
            {
                OscmsCertificate *certificates;
                size_t certificates_count;
            } certificates;
        } identifier;
    } OscmsSignerIdentifier;

    // IEEE 1609.2.1-2022 Section 7.5.12
    typedef enum OscmsScopedCertificateRequestType
    {
        OSCMS_SCOPED_CERTIFICATE_REQUEST_TYPE_NONE            = 0,
        OSCMS_SCOPED_CERTIFICATE_REQUEST_TYPE_RA_ACA          = 1,
        OSCMS_SCOPED_CERTIFICATE_REQUEST_TYPE_ECA_EE          = 2,
        OSCMS_SCOPED_CERTIFICATE_REQUEST_TYPE_EE_RA           = 3,
        OSCMS_SCOPED_CERTIFICATE_REQUEST_TYPE_EE_RA_SUCCESSOR = 4,
    } OscmsScopedCertificateRequestType;

    typedef struct OscmsScopedCertificateRequest
    {
        OscmsScopedCertificateRequestType type;
        union
        {
            OscmsEeEcaCertRequest eca_ee;
            OscmsEeRaCertRequest ee_ra;
            OscmsOctetBuffer ee_ra_successor; // Thisis an encoded EeEcaCertRequestSpdu
        } pdu;
    } OscmsScopedCertificateRequest;

    // IEEE 1609.2.1-2022 Section 7.3.44
    typedef struct OscmsSignedCertificateRequest
    {
        OscmsHashAlgorithm hashAlgorithm;
        OscmsScopedCertificateRequest tbs_request;
        OscmsSignerIdentifier signer;
        OscmsSignature signature;

        // Tracking field for memory allocated during decoding.
        // Use  oscms_empty_signed_certificate_request() to free the memory.
        OscmsSequence allocations;
    } OscmsSignedCertificateRequest;

    /**
     * Decode the SignedCertificateRequest from the buffer
     *
     * @param encoded The COER encoded SignedCertificateRequest
     * @param request The decoded OscmsSignedCertificateRequest
     * @param encoded_tbs_request The encoded TBS request portion (optional, can be NULL)
     *
     * @note get encoded_tbs_request is optional, can be NULL if not needed
     * @return 0 on success
     */
    SO_EXPORT int oscms_decode_signed_certificate_request(
        const OscmsOctetBuffer *encoded, OscmsSignedCertificateRequest *request, OscmsOctetBuffer *encoded_tbs_request);

    /**
     * Free the memory allocated during decoding of the request
     *
     * @param request The SignedCertificateRequest to be emptied
     *
     * @return
     */
    SO_EXPORT void oscms_empty_signed_certificate_request(OscmsSignedCertificateRequest *request);

    /**
     * Free the memory allocated during decoding of the request, including the object itself
     *
     * @param request The SignedCertificateRequest to be freed
     */
    SO_EXPORT void oscms_free_signed_certificate_request(OscmsSignedCertificateRequest *request);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_SIGNED_CERT_REQUEST_H
