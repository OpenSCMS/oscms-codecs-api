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

//***** Delete the following comments they are just to give a structure */

#include <string.h>

#include "oscms_codecs_api/logging.h"
#include "oscms_codecs_api/octet_buffer.h"
#include "oscms_codecs_api/oscms_utilities.h"
#include "oscms_codecs_api/signed_certificate_request.h"

SO_EXPORT void oscms_empty_signed_certificate_request(OscmsSignedCertificateRequest *request)
{
    if (!request)
    {
        oscms_log(LOG_ERR, "%s called with NULL argument", __func__);
        return;
    }

    // free every certificate in the signer identifier
    for (size_t i = 0; i < request->signer.identifier.certificates.certificates_count; i++)
    {
        oscms_empty_certificate(&request->signer.identifier.certificates.certificates[i]);
    }

    if (request->tbs_request.type == OSCMS_SCOPED_CERTIFICATE_REQUEST_TYPE_EE_RA)
        oscms_empty_ee_ra_cert_request(&request->tbs_request.pdu.ee_ra);
    else if (request->tbs_request.type == OSCMS_SCOPED_CERTIFICATE_REQUEST_TYPE_ECA_EE)
        oscms_empty_ee_eca_cert_request(&request->tbs_request.pdu.eca_ee);

    // free the rest
    oscms_empty_sequence(&request->allocations);
    (void)explicit_bzero(request, sizeof(OscmsSignedCertificateRequest));
}

SO_EXPORT void oscms_free_signed_certificate_request(OscmsSignedCertificateRequest *request)
{
    if (request)
    {
        oscms_empty_signed_certificate_request(request);
        free(request);
    }
}