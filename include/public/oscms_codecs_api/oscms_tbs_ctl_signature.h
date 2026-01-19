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

#ifndef OSCMS_TBS_CTL_SIGNATURE_H
#define OSCMS_TBS_CTL_SIGNATURE_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/dot2_data_signed.h"
#include "oscms_codecs_api/so_export.h"

    typedef struct OscmsTbsCtlSignature
    {
        OscmsCtlSeriesId series_id;
        //
        OscmsCtlSequenceNumber sequence_number;
        OscmsHashedId48 tbs_ctl_hash;
    } OscmsTbsCtlSignature;

    /**
     * Converts OscmsTbsCtlSignature to internal structure
     *
     * @param[in] tbsCtlSig The OscmsTbsCtlSignature to convert
     * @param[in] internal_void Pointer to internal structure
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_tbs_ctl_signature_to_internal(const OscmsTbsCtlSignature *tbsCtlSig, void *internal_void);

    /**
     * COER Encode an OscmsTbsCtlSignature as ScmsPdu
     *
     * @param[in] tbsCtlSig The OscmsTbsCtlSignature to encode
     * @param[out] encoded The COER-encoded OscmsTbsCtlSignature
     *
     * Produces a COER-encoded OscmsTbsCtlSignature in a form suitable for inserting into a higher-level SPDU
     * or for signing.
     *
     * @return 0 on success
     */

    SO_EXPORT int oscms_encode_tbs_ctl_signature(const OscmsTbsCtlSignature *tbsCtlSig, OscmsOctetBuffer *encoded);

    /**
     * Generate an encoded CtlSignatureSpdu
     *
     * @param[in] args The OscmsDot2DataSignedArgs to encode
     * @param[out] encoded The COER-encoded OscmsTbsCtlSignature
     *
     * The payload in the provided arguments should be a COER-encoded OscmsTbsCtlSignature as produced by
     * `oscms_encode_tbs_ctl_signature`.
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_encode_ctl_signature_spdu(const OscmsDot2DataSignedArgs *args, OscmsOctetBuffer *encoded);
#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_TBS_CTL_SIGNATURE_H
