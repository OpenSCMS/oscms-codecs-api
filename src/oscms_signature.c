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

#include "oscms_codecs_api/octet_buffer.h"
#include "oscms_codecs_api/oscms_ecc_curve.h"
#include "oscms_codecs_api/oscms_signature.h"

SO_EXPORT void oscms_empty_signature(OscmsSignature *oscms_signature)
{
    if (oscms_signature)
    {
        if (oscms_signature->type == OSCMS_SIGNATURE_TYPE_SM2)
        {
            oscms_empty_octet_buffer(&oscms_signature->rsig.value);
        }
        else
        {
            oscms_empty_ecc_curve_point(&oscms_signature->rsig.curve_point);
        }
        oscms_empty_octet_buffer(&oscms_signature->s_sig);
        (void)explicit_bzero(oscms_signature, sizeof(*oscms_signature));
    }
}

SO_EXPORT void oscms_free_signature(OscmsSignature *oscms_signature)
{
    if (oscms_signature)
    {
        oscms_empty_signature(oscms_signature);
        free(oscms_signature);
    }
}
