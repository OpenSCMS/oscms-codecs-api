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
 * @file oscms_eca_ee_cert_response.h
 *
 * Encoding of an EcaEeCertResponse PDU - Iee1609.2.1-2022 Section 7.3.30
 *
 * This PDU is encoded into an Ieee1609Dot2Data-Signed structure as part of an
 * EcaEeCertResponseSpdu (Ieee1609.2.1-2022 Section 7.4.9).
 */

#ifndef OSCMS_ECA_EE_CERT_RESPONSE_H
#define OSCMS_ECA_EE_CERT_RESPONSE_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_certificate.h"
#include "oscms_codecs_api/so_export.h"

    typedef struct OscmsEcaEeCertResponse
    {
        OscmsTime32 generation_time;
        OscmsHashedId8 request_hash;
        OscmsCertificate *eca_cert_chain;
        size_t eca_cert_chain_count;
        OscmsCertificate certificate;
        OscmsOctetBuffer *private_key_info;
    } OscmsEcaEeCertResponse;

    /**
     * @brief Encode am OscmsEcaEeCertResponse as an ScmsPdu
     *
     * See IEEE 1609.2-2022 specification 7.3.30
     *
     * @param[in] eca_ee_cert_response A pointer to the API representation to be encoded
     * @param[in] buffer A pointer to the buffer to which the encoded data will be written
     *
     * @return 0 on success, non-zero on failure
     */
    SO_EXPORT int oscms_encode_eca_ee_cert_response(
        const OscmsEcaEeCertResponse *eca_ee_cert_response, OscmsOctetBuffer *buffer);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_ECA_EE_CERT_RESPONSE_H
