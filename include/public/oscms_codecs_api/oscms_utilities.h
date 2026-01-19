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
 * @file utilities.h
 *
 * @brief General Utility functions
 *
 * This module defines various utility functions for use by concrete implementations of the API
 * and clients of the API.
 */

#ifndef OSCMS_UTILITIES_H
#define OSCMS_UTILITIES_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_sequence.h"
#include "oscms_codecs_api/so_export.h"

    /**
     * @brief Returns the minimum of two size_t values
     *
     * @param a The first size_t value
     * @param b The second size_t value
     *
     * @return The minimum of the two size_t values
     */
    static inline size_t size_t_min(size_t a, size_t b)
    {
        return a < b ? a : b;
    }

    /**
     * @brief Allocates memory and tracks it for later deallocation.
     *
     * @param size The number of bytes to allocate
     * @param tracker The sequence in which to track the allocated memory
     *
     * The allocated memory is initialized to all-bits-zero
     *
     * @return A pointer to the allocated memory or NULL
     */
    SO_EXPORT void *oscms_tracked_malloc(size_t size, OscmsSequence *tracker);

    /**
     * @brief Allocates memory and tracks it for later deallocation a la calloc
     *
     * @param count The number of elements to allocate
     * @param size The number of bytes to allocate per element
     * @param tracker The sequence in which to track the allocated memory
     *
     * The allocated memory is initialized to all-bits-zero
     *
     * @return A pointer to the allocated memory or NULL
     */
    SO_EXPORT void *oscms_tracked_calloc(size_t count, size_t size, OscmsSequence *tracker);

    /**
     * @brief Add a pointer to the OscmsSequence's memory cache
     *
     * @param tracker The OscmsSequence structure
     * @param ptr The pointer to add
     *
     * @return 0 on success, -1 on failure
     */
    SO_EXPORT int oscms_track_other(void *ptr, OscmsSequence *tracker);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // OSCMS_UTILITIES_H
