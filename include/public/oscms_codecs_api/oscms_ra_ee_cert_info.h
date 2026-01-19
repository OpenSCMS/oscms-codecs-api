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
 * @file oscms_ra_ee_cert_info.h
 *
 * Encoding of an RaEeCertInfo PDU - Iee1609.2.1-2022 Section 7.3.38
 *
 * This PDU is used by the RA to send an EeRaEnrollmentCertAckSpdu (Ieee1609.2.1-2022 Section 7.4.21).
 *
 * The Pdu is also the payload for an RaEeCertIfnoSpdu (Ieee1609.2.1-2022 Section 7.4.20).
 *
 * ACPC Tree ID is not supported.
 *
 */

#ifndef OSCMS_RA_EE_CERT_INFO_H
#define OSCMS_RA_EE_CERT_INFO_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/so_export.h"

    typedef struct OscmsRaEeCertInfo
    {
        OscmsTime32 generation_time;
        OscmsIValue current_i;
        OscmsHashedId8 request_hash;
        OscmsTime32 next_download_time;

        // OscmsOctetBuffer *acpc_tree_id; // Not supported

    } OscmsRaEeCertInfo;

    /**
     * Encode an RaEeCertInfo PDU as an ScmsPdu into an OscmsOctetBuffer
     *
     * @param[in] ra_ee_cert_info A pointer to the OscmsRaEeCertInfo to encode
     * @param[out] encoded_ra_ee_cert_info A pointer to the output COER-encoded RaEeCertInfo
     *
     * @return 0 on success, -1 on failure
     */
    SO_EXPORT int oscms_encode_ra_ee_cert_info(
        const OscmsRaEeCertInfo *ra_ee_cert_info, OscmsOctetBuffer *encoded_ra_ee_cert_info);

    /**
     * Encode an RaEeCertInfo PDU into a COER-encoded RaEeCertInfoSpdu
     *
     * The SPDU is simply an Ieee1609Dot2Data-unsecured with the encoded RaEeCertInfo as the payload
     *
     * @param[in] ra_ee_cert_info A pointer to the OscmsRaEeCertInfo to encode
     * @param[out] encoded_spdu A pointer to the output COER-encoded RaEeCertInfoSpdu
     *
     * @return 0 on success, -1 on failure
     */
    SO_EXPORT int oscms_encode_ra_ee_cert_info_spdu(
        const OscmsRaEeCertInfo *ra_ee_cert_info, OscmsOctetBuffer *encoded_spdu);
#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_RA_EE_CERT_INFO_H
