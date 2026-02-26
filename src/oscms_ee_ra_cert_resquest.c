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

#include <string.h>

#include "oscms_codecs_api/logging.h"
#include "oscms_codecs_api/octet_buffer.h"
#include "oscms_codecs_api/oscms_ee_ra_cert_request.h"
#include "oscms_codecs_api/oscms_utilities.h"

SO_EXPORT void oscms_empty_ee_ra_cert_request(OscmsEeRaCertRequest *ee_ra_cert_request)
{
    if (!ee_ra_cert_request)
    {
        oscms_log(LOG_ERR, "%s called with NULL argument", __func__);
        return;
    }

    oscms_empty_tbs_certificate(&ee_ra_cert_request->tbs_certificate);
    oscms_empty_sequence(&ee_ra_cert_request->allocations);
    (void)explicit_bzero(ee_ra_cert_request, sizeof(OscmsEeRaCertRequest));
}

SO_EXPORT void oscms_free_ee_ra_cert_request(OscmsEeRaCertRequest *ee_ra_cert_request)
{
    if (ee_ra_cert_request)
    {
        oscms_empty_ee_ra_cert_request(ee_ra_cert_request);
        free(ee_ra_cert_request);
    }
}
