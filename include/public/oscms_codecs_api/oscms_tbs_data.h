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

#ifndef OSCMS_TO_BE_SIGNED_DATA_H
#define OSCMS_TO_BE_SIGNED_DATA_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/so_export.h"

    /**
     *  @brief Generate and encode the ToBeSignedData_t structure
     *
     * @param[in] args A pointer to the input arguments
     * @param[out] buffer Pointer to the buffer where the encoded ToBeSignedData_t will be stored
     *
     * @return 0 on success, and -1 on failure
     */
    SO_EXPORT int oscms_encode_tbs_data(
        const OscmsOctetBuffer *tbs_data_payload, const OscmsPsid tbs_data_payload_psid, OscmsOctetBuffer *buffer);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // OSCMS_TBS_DATA_H
