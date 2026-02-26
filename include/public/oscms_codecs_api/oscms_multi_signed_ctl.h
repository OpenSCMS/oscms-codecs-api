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

#ifndef OSCMS_MULTI_SIGNED_CTL_H
#define OSCMS_MULTI_SIGNED_CTL_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

    /**
     * @file multi-signed-ctl.h
     *
     * @brief Functions and types for a MultiSignedCtl and MultiSignedCtlSpdu
     *
     * See IEEE 1609.2.1-2022 Section 7.4.17 and 7.3.11
     *
     */

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_certificate.h"
#include "oscms_codecs_api/oscms_tbs_ctl_signature.h"
#include "oscms_codecs_api/so_export.h"

    // See Ieee 1609.2.1-2022 Section 7.3.18
    typedef OscmsHashedId48 OscmsCtlElectorEntry;

    // See Ieee 1609.2.1-2022 Section 7.3.19
    typedef OscmsHashedId32 OscmsRootCaEntry;

    // See Ieee 1609.2.1-2022 Section 7.3.15
    typedef struct OscmsFullIeeeTbsCtl
    {
        OscmsCtlSeriesId series_id;
        OscmsCtlSequenceNumber sequence_number;
        OscmsTime32 effective_date;

        // Array of OscmsCtlElectorEntry values
        OscmsCtlElectorEntry *elector_approve;
        size_t num_elector_approve;

        // Array of OscmsCtlElectorEntry values
        OscmsCtlElectorEntry *elector_remove;
        size_t num_elector_remove;

        // Array of OscmsRootCaEntry values
        OscmsRootCaEntry *root_ca_approve;
        size_t num_root_ca_approve;

        // Array of OscmsRootCaEntry values
        OscmsRootCaEntry *root_ca_remove;
        size_t num_root_ca_remove;

        bool quorum_present;
        long quorum;
    } OscmsFullIeeeTbsCtl;

    // See Ieee 1609.2.1-2022 Section 7.3.11
    typedef struct OscmsMultiSignedCtl
    {
        OscmsFullIeeeTbsCtl full_ieee_tbs_ctl;

        // Array of pre-encoded OscmsCertificates
        OscmsOctetBuffer *certs;
        size_t cert_count;

        // An array of pre-encoded CtlSignatureSpdus
        OscmsOctetBuffer *ctl_signatures;
        size_t signature_count;

    } OscmsMultiSignedCtl;

    /**
     * Convert an API representation of a MultiSignedCtl to the internal representation.
     *
     * @param multi_signed_ctl The MultiSignedCtl to convert
     * @param internal_void The internal representation of the MultiSignedCtl
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_multi_signed_ctl_to_internal(const OscmsMultiSignedCtl *multi_signed_ctl, void *internal_void);

    /**
     * Encode a MultiSignedCtl as an ScmsPdu
     *
     * @param multi_signed_ctl The MultiSignedCtl to be encoded
     * @param encoded TheCOER encoded ScmsPdu
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_encode_multi_signed_ctl(const OscmsMultiSignedCtl *multi_signed_ctl, OscmsOctetBuffer *encoded);

    /**
     * Encode a Signed MultiSignedCtlSpdu
     *
     * See Ieee 1609.2.1-2022 Section 7.4.17
     *
     *
     * @param multi_signed_ctl The MultiSignedCtl to be encoded
     * @param encoded The COER encoded MultiSignedCtlSpdu
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_encode_multi_signed_ctl_spdu(
        const OscmsMultiSignedCtl *multi_signed_ctl, OscmsOctetBuffer *encoded);

    /**
     * Encode a FullIeeeTbsCtl
     *
     * @param full_ieee_ctl The FullIeeeTbsCtl to be encoded
     * @param encoded The COER encoded FullIeeeTbsCtl
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_encode_full_ieee_ctl(const OscmsFullIeeeTbsCtl *full_ieee_ctl, OscmsOctetBuffer *encoded);

    /**
     * Empty a MultiSignedCtl structure
     *
     * @param multi_signed_ctl The MultiSignedCtl to empty
     *
     * NOTE: Do NOT call this if any internal structures are initialized with statically allocated memory
     *
     * @return void
     */
    SO_EXPORT void oscms_empty_multi_signed_ctl(OscmsMultiSignedCtl *multi_signed_ctl);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_MULTI_SIGNED_CTL_H
