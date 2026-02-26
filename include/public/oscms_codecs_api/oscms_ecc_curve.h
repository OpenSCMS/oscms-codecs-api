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
 * @file oscms_ecc_curve.h
 * @brief OpenSCMS ECC curve Point utility functions
 *
 * This header provides prototypes for converting between the API's representation
 * of an ECC curve point and the implementations internal representation.
 *
 * They are not intended to be called directly by clients of the API, but are expected to be
 * needed internally by concrete implementations (hence the use of `void *` parameters).
 *
 * Additionally, two utility functions are provided for initializing and clearing
 * an OscmsEccCurvePoint structure in a consistent way.
 *
 */
#ifndef OSCMS_ECC_CURVE_POINT_H
#define OSCMS_ECC_CURVE_POINT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/octet_buffer.h"
#include "oscms_codecs_api/oscms_sequence.h"

    /**
     * @brief Converts between the API's representation of an ECC curve point and the implementations internal
     * representation
     *
     * @param internal The internal representation of the ECC curve point.
     * @param curve_type The curve type of the internal representation (as this can not be deduced)
     * @param ecc_curve_point The ECC curve point to convert.
     * @param tracker A sequence used to track any memory allocated in generating the API representation
     *
     * If the tracker is NULL, no memory will be tracked and it is the caller's responsibility
     * to free the memory allocated by the API representation.
     *
     * @return 0 on success
     */
    int oscms_ecc_curve_point_from_internal(
        const void *internal,
        OscmsEccPointCurveType curve_type,
        OscmsEccCurvePoint *ecc_curve_point,
        OscmsSequence *tracker);

    /**
     * @brief Converts between the API's representation of an ECC curve point and the implementations internal
     * representation
     *
     * No memory tracking ability is required, as the internal representations are expected to track their own memory.
     *
     * @param ecc_curve_point The ECC curve point to convert.
     * @param internal The internal representation of the ECC curve point.
     *
     * @return 0 on success
     */
    int oscms_internal_from_ecc_curve_point(const OscmsEccCurvePoint *ecc_curve_point, void *internal);

    /**
     * @brief Initialise an API representation of the ECC curve point structure.
     *
     * @param internal The ECC curve point to initialize.
     *
     */
    static inline void oscms_ecc_curve_point_init(OscmsEccCurvePoint *ecc_curve_point)
    {
        oscms_octet_buffer_init_from_buffer(&ecc_curve_point->x, 0, 0);
        oscms_octet_buffer_init_from_buffer(&ecc_curve_point->y, 0, 0);
        ecc_curve_point->point_type = OSCMS_ECC_POINT_TYPE_NONE;
        ecc_curve_point->curve_type = OSCMS_ECC_POINT_CURVE_TYPE_NONE;
    }

    /**
     * @brief Release all memory allocated by an internal representation of the ECC curve point structure.
     *
     * @param internal The ECC curve point to initialize.
     *
     */
    static inline void oscms_empty_ecc_curve_point(OscmsEccCurvePoint *ecc_curve_point)
    {
        oscms_empty_octet_buffer(&ecc_curve_point->x);
        oscms_empty_octet_buffer(&ecc_curve_point->y);
        ecc_curve_point->point_type = OSCMS_ECC_POINT_TYPE_NONE;
        ecc_curve_point->curve_type = OSCMS_ECC_POINT_CURVE_TYPE_NONE;
    }

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_ECC_CURVE_POINT_H
