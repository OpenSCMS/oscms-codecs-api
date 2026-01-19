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

#ifndef OSCMS_CERTIFICATE_CHAIN_H
#define OSCMS_CERTIFICATE_CHAIN_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/so_export.h"

    // See Ieee1609.2.1-2022 Section 7.3.10
    typedef struct OscmsCertificateChain
    {
        // A COER-encoded MultiSignedCtlSpdu, non-optional
        OscmsOctetBuffer home_ctl;

        // A list of zero or more COER encoded certificates
        OscmsOctetBuffer *others;
        size_t others_count;
    } OscmsCertificateChain;

    /**
     * Converts an OSCMS certificate chain to an internal representation.
     *
     * @param[in] certificate_chain The OSCMS certificate chain to convert
     * @param[out] internal_void The internal representation of the certificate chain
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_certificate_chain_to_internal(
        const OscmsCertificateChain *certificate_chain, void *internal_void);

    /**
     * Encodes a certificate chain as an ScmsPdu
     *
     * @param[in] certificate_chain The certificate chain to be encoded
     * @param[out] encoded The COER encoded ScmsPdu
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_encode_certificate_chain(
        const OscmsCertificateChain *certificate_chain, OscmsOctetBuffer *encoded);

    /**
     * Encodes a certificate chain as a CertificateChainSpdu (which is an Ieee1609Dot2Data-Unsecured)
     *
     * @param[in] certificate_chain The certificate chain to be encoded
     * @param[out] encoded The COER encoded CertificateChainSpdu
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_encode_certificate_chain_spdu(
        const OscmsCertificateChain *certificate_chain, OscmsOctetBuffer *encoded);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_CERTIFICATE_CHAIN_H
