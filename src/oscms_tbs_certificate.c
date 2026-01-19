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
#include "oscms_codecs_api/oscms_tbs_certificate.h"
#include "oscms_codecs_api/oscms_utilities.h"

SO_EXPORT void oscms_tbs_certificate_init(OscmsTbsCertificate *tbs_certificate)
{
    (void)memset(tbs_certificate, 0, sizeof(*tbs_certificate));
    oscms_sequence_init(&tbs_certificate->allocations);
}

SO_EXPORT void oscms_empty_tbs_certificate(OscmsTbsCertificate *tbs_certificate)
{
    if (!tbs_certificate)
    {
        oscms_log(LOG_ERR, "%s called with NULL argument", __func__);
        return;
    }

    oscms_empty_sequence(&tbs_certificate->allocations);
    oscms_tbs_certificate_init(tbs_certificate);
}

SO_EXPORT void oscms_free_tbs_certificate(OscmsTbsCertificate *tbs_certificate)
{
    oscms_empty_tbs_certificate(tbs_certificate);
    free(tbs_certificate);
}
