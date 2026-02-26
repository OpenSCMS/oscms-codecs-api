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

#ifndef OSCMS_SIGNATURE_H
#define OSCMS_SIGNATURE_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_sequence.h"
#include "oscms_codecs_api/so_export.h"

    typedef enum OscmsSignatureType
    {
        OSCMS_SIGNATURE_TYPE_UNKNOWN,
        OSCMS_SIGNATURE_TYPE_NIST_P256,
        OSCMS_SIGNATURE_TYPE_BRAINPOOL_P256,
        OSCMS_SIGNATURE_TYPE_BRAINPOOL_P384,
        OSCMS_SIGNATURE_TYPE_NIST_P384,
        OSCMS_SIGNATURE_TYPE_SM2,
    } OscmsSignatureType;

    // See IEEE-1609.2-2022 Section 6.3.37..6.3.40
    typedef struct OscmsSignature
    {
        OscmsSignatureType type;

        // rSig
        union
        {
            OscmsOctetBuffer value;         // For OSCMS_SIGNATURE_TYPE_SM2
            OscmsEccCurvePoint curve_point; // For all others
        } rsig;

        OscmsOctetBuffer s_sig;
    } OscmsSignature;

    /**
     * @brief Release all dynamically allocated resources in an OscmsSignature
     *
     * @param oscms_signature The OSCMS representation of a Signature object
     *
     * NOTE: This function does NOT free the OscmsSignature itself
     */
    SO_EXPORT void oscms_empty_signature(OscmsSignature *oscms_signature);

    /**
     * @brief Release all dynamically allocated resources in an OscmsSignature
     *
     * @param oscms_signature The OSCMS representation of a Signature object
     *
     * NOTE: This function also frees the OscmsSignature itself
     */
    SO_EXPORT void oscms_free_signature(OscmsSignature *oscms_signature);

    // These functions are not exported to the bridge. They is intended for internal use
    // by concrete implementations, as encoding and decoding of higher level structures often need
    // to do these conversions.
    //
    // Implementation is optional

    /**
     * @brief Convert an OscmsSignature to the CODEC representation of a Signature
     *
     * @param oscms_signature The OSCMS representation of a Signature object
     * @param signature       The CODEC representation of a Signature object
     *
     *
     * @return 0 on success
     */
    int oscms_signature_to_internal(const OscmsSignature *oscms_signature, void *signature);

    /**
     * @brief Convert the CODEC representation of a Signature to an OscmsSignature
     *
     * @param signature       The CODEC representation of a Signature object
     * @param oscms_signature The OSCMS representation of a Signature object
     * @param tracker         The memory tracker. If NULL, no memory tracking will occur
     *
     * @return 0 on success
     */
    int oscms_signature_from_internal(const void *signature, OscmsSignature *oscms_signature, OscmsSequence *tracker);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // OSCMS_SIGNATURE_H
