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

/**
 * @file oscms_ee_ra_cert_request.h
 *
 * Defines types and functions involved in decoding an EeRaCertRequest
 *
 * These are always embedded in an ScmsPdu and are only received by the server - it never sends one. Thus there are no
 * encoding functions defined.
 */
#ifndef OSCMS_EE_RA_CERT_REQUEST
#define OSCMS_EE_RA_CERT_REQUEST

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_sequence.h"
#include "oscms_codecs_api/oscms_tbs_certificate.h"
#include "oscms_codecs_api/so_export.h"

    // Note that the ButteryflyExpansion type (Ieee1609.2.1-2022 Section 7.3.36) is defined as a CHOICE. However, it
    // only has one variant, which contains a single  OCTET STRING. Therefore we simply replace it with an
    // OscmsOCtetBuffer

    // Butterfly Parameters
    // IEEE 1609.2-2022 Section 7.3.35
    typedef struct OscmsButterflyParamsOriginal
    {
        OscmsOctetBuffer signing_expansion;
        OscmsPublicEncryptionKey encryption_key;
        OscmsOctetBuffer encryption_expansion;
    } OscmsButterflyParamsOriginal;

    // Additional Parameters
    // See Ieee1609.2.1-2022 Section 7.3.34
    typedef enum OscmsAdditionalParamsType
    {
        OSCMS_ADDITIONAL_PARAMS_TYPE_NONE            = 0,
        OSCMS_ADDITIONAL_PARAMS_TYPE_ORIGINAL        = 1,
        OSCMS_ADDITIONAL_PARAMS_TYPE_UNIFIED         = 2,
        OSCMS_ADDITIONAL_PARAMS_TYPE_COMPACT_UNIFIED = 3,
        OSCMS_ADDITIONAL_PARAMS_TYPE_ENCRYPTION_KEY  = 4,
    } OscmsAdditionalParamsType;

    typedef struct OscmsAdditionalParams
    {
        OscmsAdditionalParamsType type;
        union
        {
            OscmsButterflyParamsOriginal original;
            OscmsOctetBuffer unified;
            OscmsOctetBuffer compact_unified;
            OscmsPublicEncryptionKey encryption_key;
        } parameter;
    } OscmsAdditionalParams;

    // The actual request
    // IEEE 1609.2-2022 Section 7.3.33
    typedef struct OscmsEeRaCertRequest
    {
        OscmsTime32 generation_time;
        OscmsCertificateType certificate_type;
        OscmsTbsCertificate tbs_certificate;
        OscmsAdditionalParams *additional_params;

        // Structure for tracking allocated memory
        OscmsSequence allocations;

    } OscmsEeRaCertRequest;

    /**
     * Converts the internal representation of a EeRaCertRequest to the API representation.
     *
     * @param[in] internal The internal representation of the EeRaCertRequest.
     * @param[out] ee_ra_cert_request The API representation of the OSCMS_EE_RA_CERT_REQUEST.
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_ee_ra_cert_request_from_internal(
        const void *internal, OscmsEeRaCertRequest *ee_ra_cert_request);

    /**
     * Frees memory allocated for an OscmsEeRaCertRequest, but ot the structure itself.
     *
     * @param[in] ee_ra_cert_request The OSCMS_EE_RA_CERT_REQUEST to free
     *
     */
    SO_EXPORT void oscms_empty_ee_ra_cert_request(OscmsEeRaCertRequest *ee_ra_cert_request);

    /**
     * Frees memory allocated for an OscmsEeRaCertRequest.
     *
     * @param[in] ee_ra_cert_request The OSCMS_EE_RA_CERT_REQUEST to free
     *
     */
    SO_EXPORT void oscms_free_ee_ra_cert_request(OscmsEeRaCertRequest *ee_ra_cert_request);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_EE_RA_CERT_REQUEST
