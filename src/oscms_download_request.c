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

#include "oscms_codecs_api/octet_buffer.h"
#include "oscms_codecs_api/oscms_download_request.h"
#include "oscms_codecs_api/oscms_utilities.h"

SO_EXPORT void oscms_empty_ee_ra_download_request(OscmsEeRaDownloadRequest *request)
{
    if (request)
    {
        oscms_empty_octet_buffer(&request->filename);
        (void)memset(request, 0, sizeof(OscmsEeRaDownloadRequest));
    }
}

SO_EXPORT void oscms_free_ee_ra_download_request(OscmsEeRaDownloadRequest *request)
{
    oscms_empty_ee_ra_download_request(request);
    free(request);
}
