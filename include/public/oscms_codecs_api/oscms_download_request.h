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
 * @file oscms_download_request.h
 *
 * Decode an EeRaDownloadRequest entity - See IEEE 1609.2.1-2022 Section 7.3.39
 *
 * This is always encoded as an ScmsPdu, but may either be the body of an EeRaDownloadRequestPlainSpdu (See Ieee
 * 1609.2.1-2022 Section 7.4.13) or deeply embedded in an EeRaDownloadRequestSpdu (See Ieee 1609.2.1-2022
 * Section 7.4.14) which is Signed and Encrypted.
 */

#ifndef OSCMS_DOWNLOAD_REQUEST_PLAIN_H
#define OSCMS_DOWNLOAD_REQUEST_PLAIN_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/so_export.h"

    // See IEEE 1609.2.1-2022 Section 7.3.39
    typedef struct OscmsEeRaDownloadRequest
    {
        OscmsTime32 generation_time;
        OscmsOctetBuffer filename;
    } OscmsEeRaDownloadRequest;

    /**
     * Decode an EeRaDownloadRequest entity
     *
     * @param encoded The EeRaDownloadRequest COER encoded as an ScmsPdu
     * @param request The decoded OscmsEeRaDownloadRequest
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_decode_ee_ra_download_request(
        const OscmsOctetBuffer *encoded, OscmsEeRaDownloadRequest *request);

    /**
     * Completely decode an EeRaDownloadRequestPlainSpdu
     *
     * This is an EeRaDownloadRequest encoded as an ScmsPDu and wrapped in an Ieee1609Dot2Data-Unsecured
     *
     * @param encoded The COER encoded EeRaDownloadRequestPlainSpdu
     * @param request The decoded OscmsEeRaDownloadRequest
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_decode_ee_ra_download_request_plain_spdu(
        const OscmsOctetBuffer *encoded, OscmsEeRaDownloadRequest *request);

    /**
     * Free the memory allocated within an  OscmsEeRaDownloadRequest
     *
     * @param request The OscmsEeRaDownloadRequest
     */
    SO_EXPORT void oscms_empty_ee_ra_download_request(OscmsEeRaDownloadRequest *request);

    /**
     * Free the memory allocated within an OscmsEeRaDownloadRequest, including the object itself
     *
     * @param request The OscmsEeRaDownloadRequest
     */
    SO_EXPORT void oscms_free_ee_ra_download_request(OscmsEeRaDownloadRequest *request);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_DOWNLOAD_REQUEST_PLAIN_H
