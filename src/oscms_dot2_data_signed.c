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

#include <stdlib.h>
#include <string.h>

#include "oscms_codecs_api/dot2_data_signed.h"
#include "oscms_codecs_api/octet_buffer.h"

SO_EXPORT void oscms_empty_signed_data(OscmsSignedData *signed_data)
{
    if (signed_data)
    {
        oscms_empty_octet_buffer(&signed_data->payload);
        oscms_empty_signature(&signed_data->signature);
        oscms_empty_certificate(&signed_data->signer_certificate);
        (void)explicit_bzero(signed_data, sizeof(OscmsSignedData));
    }
}

SO_EXPORT void oscms_free_signed_data(OscmsSignedData *signed_data)
{
    if (signed_data)
    {
        oscms_empty_signed_data(signed_data);
        free(signed_data);
    }
}
