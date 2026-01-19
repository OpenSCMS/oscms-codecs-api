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

#ifndef OSCMS_COMPOSITE_CRL_H
#define OSCMS_COMPOSITE_CRL_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_multi_signed_ctl.h"
#include "oscms_codecs_api/oscms_secured_crl.h"
#include "oscms_codecs_api/oscms_sequence.h"
#include "oscms_codecs_api/so_export.h"

    // See Ieee 1609.2.1-2022 Section 7.3.9
    typedef struct OscmsCompositeCrl
    {
        // Each OscmsOctetBuffer is a COER-encoded SecuredCrl SPDU
        OscmsOctetBuffer *secured_crls;
        size_t secured_crls_count;

        // This is a COER-encoded MultiSignedCtlSpdu
        OscmsOctetBuffer home_ctl;

    } OscmsCompositeCrl;

    /**
     * Encodes a composite CRL as an ScmsPdu
     *
     * @param[in] composite_crl The composite CRL to be encoded
     * @param[out] encoded The encoded composite CRL ScmsPdu
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_encode_composite_crl(const OscmsCompositeCrl *composite_crl, OscmsOctetBuffer *encoded);

    /**
     * Encodes a composite CRL as a CompositeCrlSpdu
     *
     * @param[in] composite_crl The composite CRL to be encoded
     * @param[out] encoded The encoded composite CRL SPDU
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_encode_composite_crl_spdu(const OscmsCompositeCrl *composite_crl, OscmsOctetBuffer *encoded);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_COMPOSITE_CRL_H
