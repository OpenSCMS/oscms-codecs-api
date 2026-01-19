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

#ifndef OSCMS_CODECS_CERT_MGT_INFO_STATUS_H
#define OSCMS_CODECS_CERT_MGT_INFO_STATUS_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_signature.h"
#include "oscms_codecs_api/so_export.h"

    /**
     * @file cert_mgt_info_status.h
     *
     * @brief Function for encoding Certificate Management PDUs
     *
     * The CertManagementPdu is the content of what will be signed and wrapped in an IeeeDot2Data-Signed SPDU.
     * In this context the IeeeDot2Data-Signed SPDU is called as Certificate Management Info Status SPDU.
     * Note that this SPDU is an outer IeeeDot2Data-Signed SPDU containing an inner ScmsPdu.
     * Therefore, to compose and encode a Certificate Management Info Status SPDU, you must follow these steps:
     *
     * 1. Encode the inner ScmsPdu by calling `oscms_encode_cert_mgt_pdu`
     * 2. Genrate the signature for the inner ScmsPdu per the specification
     * 3. Encode the outer IeeeDot2Data-Signed SPDU by calling `oscms_encode_dot2_data_signed`
     *
     * The caller will need to release the memory allocated for the inner ScmsPdu and the outer IeeeDot2Data-Signed SPDU
     *
     */

    //------------------------------------------------------------------------------
    // Types and constants

    typedef struct OscmsCertManagementPduArgs
    {
        OscmsPsid **ma_psid_lists;     // list of lists of PSIDs (i.e. OscmsPsid ma_psid_lists[ma_count][])
        size_t *ma_psid_list_counts;   // Sizes of each list of PSIDs (size_t ma_psid_list_counts[ma_count])
        OscmsTime32 *ma_updated_times; // Updated times (OscmsTime32 ma_updated_times[ma_count])
        size_t ma_count;

        OscmsCtlSequenceNumber
            *ctl_sequence_numbers;          // Sequence numbers (OscmsCtlSequenceNumber ctl_sequence_numbers[ctl_count])
        uint8_t **ctl_series_ids;           // Series IDs (OscmsCtlSeriesId ctl_series_ids[ctl_count])
        OscmsTime32 *ctl_last_update_times; // Updated times (OscmsTime32 ctl_last_update_times[ctl_count])
        size_t ctl_count;

        uint8_t **crl_craca_ids;         // CRACAs (OscmsHashedId8 *crl_craca_ids[crl_count])
        OscmsCrlSeries *crl_series_list; // Series IDs (OscmsCrlSeries crl_series_list[crl_count])
        OscmsTime32 *crl_issue_dates;    // Issue dates (OscmsTime32 crl_issue_dates[crl_count])
        size_t crl_count;

        OscmsTime32 ca_ccf_updated_time;
        OscmsTime32 ra_updated_time;
    } OscmsCertManagementPduArgs;

    /**
     * @brief Encode a ScmsPdu scoped for a CertManagementPdu
     *
     * See IEEE 1609.2.1-2022 specification 7.3.8
     *
     * @param[in] args A pointer to the input arguments
     * @param[out] spdu A pointer to the output SPDU
     *
     * The caller is responsible for freeing the memory allocated for the output SPDU
     *
     * @return 0 on success, and the provided `spdu` will contain the encoded SPDU and length.
     */

    SO_EXPORT int oscms_encode_cert_mngt_pdu(const OscmsCertManagementPduArgs *args, OscmsOctetBuffer *spdu);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // OSCMS_CODECS_CERT_MGT_INFO_STATUS_H
