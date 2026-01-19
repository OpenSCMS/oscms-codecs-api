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

#ifndef OSCMS_ACA_RESPONSE_H
#define OSCMS_ACA_RESPONSE_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/dot2_data_encrypted.h"
#include "oscms_codecs_api/dot2_data_signed.h"
#include "oscms_codecs_api/oscms_aca_ee_cert_response.h"
#include "oscms_codecs_api/so_export.h"

    /**
     * @brief Encode an AcaResponse with private (signed and encrypted) data
     *
     * @param encrypted_signed_data Pointer to the signed data arguments
     * @param encoded Pointer to the output encoded octet buffer
     *
     * @return int 0 on success, -1 on failure
     */
    SO_EXPORT int oscms_encode_aca_response_private(
        const OscmsDot2DataSignedArgs *encrypted_signed_data, OscmsOctetBuffer *encoded);

    /**
     * @brief Encode an AcaResponse with encrypted data using CUBK
     *
     * @param dot2_data_encrypted Pointer to the encrypted data
     * @param encoded Pointer to the output encoded octet buffer
     *
     * @return int 0 on success, -1 on failure
     */
    SO_EXPORT int oscms_encode_aca_response_cubk(
        const OscmsDot2DataEncrypted *dot2_data_encrypted, OscmsOctetBuffer *encoded);

    /**
     * @brief Encode an AcaResponse with plain data
     *
     * @param plain Pointer to the plain AcaEeCertResponse data
     * @param encoded Pointer to the output encoded octet buffer
     *
     * @return int 0 on success, -1 on failure
     */
    SO_EXPORT int oscms_encode_aca_response_plain(const OscmsAcaEeCertResponse *plain, OscmsOctetBuffer *encoded);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_ACA_RESPONSE_H
