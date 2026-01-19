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

#ifndef OPENSCMS_RA_EE_CERT_ACK_H
#define OPENSCMS_RA_EE_CERT_ACK_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_signature.h"
#include "oscms_codecs_api/so_export.h"

    typedef struct OscmsRaEeCertAck
    {
        OscmsTime32 generation_time;
        OscmsHashedId8 request_hash;
        OscmsTime32 next_dl_time;
        OscmsIValue first_i;
    } OscmsRaEeCertAck;

    /**
     * @brief Encode RaEeCertAck structure into COER-encoded ScmsPdu:EeRaInterfacePdu:eeRaCertAck
     *
     * See IEEE 1609.2-2022 specification 7.3.37
     *
     * @param[in] ra_ee_cert_ack A pointer to the OscmsRaEeCertAck to encode
     * @param[out] encoded_ra_ee_cert_ack A pointer to the output COER-encoded RaEeCertAck
     *
     * `oscms_empty_octet_buffer()` must be called on the output buffer
     *
     * @return 0 on success, non-zero on failure
     */
    SO_EXPORT int oscms_encode_ra_ee_cert_ack(
        const OscmsRaEeCertAck *ra_ee_cert_ack, OscmsOctetBuffer *encoded_ra_ee_cert_ack);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OPENSCMS_RA_EE_CERT_ACK_H
