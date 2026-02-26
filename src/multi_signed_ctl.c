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

#include <string.h>

#include "oscms_codecs_api/logging.h"
#include "oscms_codecs_api/octet_buffer.h"
#include "oscms_codecs_api/oscms_multi_signed_ctl.h"
#include "oscms_codecs_api/oscms_utilities.h"

SO_EXPORT void oscms_empty_multi_signed_ctl(OscmsMultiSignedCtl *msc)
{
    if (!msc)
    {
        return;
    }

    size_t i;

    for (i = 0; msc->full_ieee_tbs_ctl.elector_approve && i < msc->full_ieee_tbs_ctl.num_elector_approve; i++)
    {
        (void)explicit_bzero(&msc->full_ieee_tbs_ctl.elector_approve[i], sizeof(OscmsCtlElectorEntry));
    }
    free(msc->full_ieee_tbs_ctl.elector_approve);

    for (i = 0; msc->full_ieee_tbs_ctl.elector_remove && i < msc->full_ieee_tbs_ctl.num_elector_remove; i++)
    {
        (void)explicit_bzero(&msc->full_ieee_tbs_ctl.elector_remove[i], sizeof(OscmsCtlElectorEntry));
    }
    free(msc->full_ieee_tbs_ctl.elector_remove);

    for (i = 0; msc->full_ieee_tbs_ctl.root_ca_approve && i < msc->full_ieee_tbs_ctl.num_root_ca_approve; i++)
    {
        (void)explicit_bzero(&msc->full_ieee_tbs_ctl.root_ca_approve[i], sizeof(OscmsRootCaEntry));
    }
    free(msc->full_ieee_tbs_ctl.root_ca_approve);

    for (i = 0; msc->full_ieee_tbs_ctl.root_ca_remove && i < msc->full_ieee_tbs_ctl.num_root_ca_remove; i++)
    {
        (void)explicit_bzero(&msc->full_ieee_tbs_ctl.root_ca_remove[i], sizeof(OscmsRootCaEntry));
    }
    free(msc->full_ieee_tbs_ctl.root_ca_remove);

    if (msc->certs)
    {
        for (i = 0; i < msc->cert_count; i++)
        {
            oscms_empty_octet_buffer(&msc->certs[i]);
        }
        free(msc->certs);
    }

    if (msc->ctl_signatures)
    {
        for (i = 0; i < msc->signature_count; i++)
        {
            oscms_empty_octet_buffer(&msc->ctl_signatures[i]);
        }
        free(msc->ctl_signatures);
    }

    (void)explicit_bzero(msc, sizeof(OscmsMultiSignedCtl));
}
