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

/**
 * @file oscms_secured_crl.h
 * @brief Contains the definition of the Secured CRL, as defined in Ieee 1609.2-2022 Section 7.4.5.3
 *
 * A SecuredCrl, while not explicitly defined as an SPDU, is actually an Ieee1609Dot2Data-Signed SPDU
 * with a CrlContents as the payload and a unique PSID (CrlPsid).
 *
 * The method to encode a SecuredCrl as an SPDU is a wrapper for `oscms_encode_dot2_data_signed`which
 * enforces the PSID constraint.
 *
 */

#ifndef OSCMS_SECURED_CRL_H
#define OSCMS_SECURED_CRL_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/dot2_data_signed.h"
#include "oscms_codecs_api/so_export.h"

    // See Ieee 1609.2-2022 Section 7.3.6
    typedef struct OscmsHashBasedRevocationInfo
    {
        OscmsHashedId10 id;
        OscmsTime32 expiry;
    } OscmsHashBasedRevocationInfo;

    // See Ieee 1609.2-2022 Section 7.3.5
    typedef struct OscmsTbsHashIdCrl
    {
        uint32_t crl_serial;

        // Array of revocation entries
        OscmsHashBasedRevocationInfo *revocation_info;
        size_t revocation_info_count;

    } OscmsTbsHashIdCrl;

    // See Ieee 1609.2-2022 Section 7.3.12
    typedef struct OscmsIndividualRevocation
    {
        OscmsLinkageSeed linkage_seed_1;
        OscmsLinkageSeed linkage_seed_2;
    } OscmsIndividualRevocation;

    // See Ieee 1609.2-2022 Section 7.3.11
    typedef struct OscmsIMaxGroup
    {
        uint8_t i_max;
        OscmsIndividualRevocation *revocations;
        size_t revocations_count;

        OscmsLinkageSeed *single_seeds;
        size_t single_seeds_count;
    } OscmsIMaxGroup;

    // See Ieee 1609.2-2022 Section 7.3.10
    typedef struct OscmsLaGroup
    {
        OscmsLaId la1_id;
        OscmsLaId la2_id;
        OscmsIMaxGroup *imax_groups;
        size_t imax_groups_count;
    } OscmsLaGroup;

    // See Ieee 1609.2-2022 Section 7.3.9
    typedef struct OscmsJMaxGroup
    {
        uint8_t j_max;
        OscmsLaGroup *groups;
        size_t groups_count;
    } OscmsJMaxGroup;

    // See Ieee 1609.2-2022 Section 7.3.13
    typedef struct OscmsGroupCrlEntry
    {
        uint16_t i_max;
        OscmsLaId la1_id;
        OscmsLinkageSeed linkage_seed_1;
        OscmsLaId la2_id;
        OscmsLinkageSeed linkage_seed_2;
    } OscmsGroupCrlEntry;

    typedef struct OscmsGroupSingleSeedCrlEntry
    {
        uint16_t i_max;
        OscmsLaId la_id;
        OscmsLinkageSeed linkage_seed;
    } OscmsGroupSingleSeedCrlEntry;

    // See Ieee 1609.2-2022 Section 7.3.7
    typedef struct OscmsTbsLvCrl
    {
        OscmsIValue i_rev;
        uint8_t index_within_i;

        OscmsJMaxGroup *individual; // OPTIONAL
        size_t individual_count;

        OscmsGroupCrlEntry *groups; // OPTIONAL
        size_t groups_count;

        OscmsGroupSingleSeedCrlEntry *groups_single_seed; // OPTIONAL
        size_t groups_single_seed_count;
    } OscmsTbsLvCrl;

    // See Ieee 1609.2-2022 Section 7.3.8
    //
    // This is basically a TbsLvCrl with all OPTIONAL fields present
    typedef OscmsTbsLvCrl OscmsTbsLvCrlWithAlgorithmId;

    // See Ieee 1609.2-2022 Section 7.3.3
    typedef enum OscmsTypeSpecificCrlContentsType
    {
        OSCMS_TSCC_NONE,
        OSCMS_TSCC_FULL_HASH,
        OSCMS_TSCC_DELTA_HASH,
        OSCMS_TSCC_FULL_LINKED,
        OSCMS_TSCC_DELTA_LINKED,
        OSCMS_TSCC_FULL_LINKED_WITH_ALG,
        OSCMS_TSCC_DELTA_LINKED_WITH_ALG,
    } OscmsTypeSpecificCrlContentsType;

    typedef struct OscmsTypeSpecificCrlContents
    {
        OscmsTypeSpecificCrlContentsType type;
        union
        {
            OscmsTbsHashIdCrl full_hash_crl;
            OscmsTbsHashIdCrl delta_hash_crl;
            OscmsTbsLvCrl full_linked_crl;
            OscmsTbsLvCrl delta_linked_crl;
            OscmsTbsLvCrlWithAlgorithmId full_linked_crl_with_alg;
            OscmsTbsLvCrlWithAlgorithmId delta_linked_crl_with_alg;
        } contents;

    } OscmsTypeSpecificCrlContents;

    // See Ieee 1609.2-2022 Sections 7.4.5.3 and 7.3.2
    typedef struct OscmsCrlContents
    {
        OscmsCrlSeries crl_series;
        OscmsHashedId8 crl_craca;
        OscmsTime32 issue_date;
        OscmsTime32 next_crl;

        bool priority_info_present; // Avoids having to dynamically allocate a 1 byte array
        uint8_t priority_info;

        OscmsTypeSpecificCrlContents type_specific;
    } OscmsCrlContents;

    // See Ieee 1609.2-2022 Section 7.4.5.3
    // Syntactic sugar as a SecuredCrl is actually a Ieee1609Dot2Data-Signed with a CrlContents
    // as the payload.
    //
    typedef OscmsCrlContents OscmsSecuredCrl;

    /**
     * Encode an OscmsSecuredCrl into a COER-encoded SecuredCrl
     *
     * @param secured_crl The oscmsSecuredCrl to encode
     * @param encoded The COER-encoded SecuredCrl
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_encode_crl_contents(const OscmsSecuredCrl *secured_crl, OscmsOctetBuffer *encoded);

    /**
     * Encode a SecuredCrl PDU along with its signature into a COER-encoded SecuredCrlSpdu
     *
     * @param secured_crl The SecuredCrl and signature information to encode
     * @param encoded The COER-encoded SecuredCrlSpdu
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_encode_secured_crl_spdu(const OscmsDot2DataSignedArgs *secured_crl, OscmsOctetBuffer *encoded);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_SECURED_CRL_H
