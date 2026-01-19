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

#ifndef OSCMS_EE_ECA_CERT_REQUEST
#define OSCMS_EE_ECA_CERT_REQUEST

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/so_export.h"
#include "oscms_tbs_certificate.h"

    typedef struct OscmsEeEcaCertRequest
    {
        OscmsTime32 generation_time;
        OscmsCertificateType certificate_type;
        OscmsTbsCertificate tbs_certificate;
        OscmsOctetBuffer *canonical_id;

        OscmsSequence allocations;
    } OscmsEeEcaCertRequest;

    /**
     * Converts the internal representation of a EeEcaCertRequest to the API representation.
     *
     * @param[in] internal The internal representation of the EeEcaCertRequest.
     * @param[out] ee_ra_cert_request The API representation of the EeEcaCertRequest.
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_ee_eca_cert_request_from_internal(
        const void *internal, OscmsEeEcaCertRequest *ee_eca_cert_request);

    /**
     * Frees memory allocated for an OscmsEeEcaCertRequest, but not the structure itself.
     *
     * @param[in] ee_ra_cert_request The OscmsEeEcaCertRequest to free
     *
     */
    SO_EXPORT void oscms_empty_ee_eca_cert_request(OscmsEeEcaCertRequest *ee_eca_cert_request);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_EE_ECA_CERT_REQUEST
