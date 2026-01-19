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
 * @file octet-buffer.h
 *
 * @brief A set of utility functions for working with OscmsOctetBuffer structures
 *
 * Generally, across the API we discourage passing a buffer as separate pointer and length values.
 * Instead, we pass a single OscmsOctetBuffer structure, which makes it less likely that the
 * two values will become out of sync.
 *
 * This module
 * contains a set of generic functions for working with OscmsOctetBuffer structures and is intended for use by both API
 * clients and concrete implementations of the API.
 *
 * Functions come in two flavors: those which allocate OscmsOctetBuffer structures (these use names containing `new`
 * or `duplicate`)and those which initialiaze an existing one (with names containing "init" or "copy").
 *
 */
#ifndef OSCMS_OCTET_BUFFER_H
#define OSCMS_OCTET_BUFFER_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <stdbool.h>

#include "oscms_codecs_api/base_types.h"
#include "oscms_codecs_api/oscms_sequence.h"
#include "oscms_codecs_api/so_export.h"

    //------------------------------------------------------------------------------
    // API Functions

    /**
     * @brief Create a new OscmsOctetBuffer structure
     *
     * Creates a new, but empty, OscmsOctetBuffer structure.
     *
     * Use oscms_free_octet_buffer to free the buffer returned by oscms_free_octet_buffer and any enclosed data.
     *
     * @return A pointer to the new OscmsOctetBuffer structure or NULL
     */
    SO_EXPORT OscmsOctetBuffer *oscms_octet_buffer_new(void);

    /**
     * @brief Create a new OscmsOctetBuffer structure from an array of bytes
     *
     * Creates a new, but empty, OscmsOctetBuffer structure initialized with a copy of the
     * specified data.
     *
     * Use oscms_free_octet_buffer to free the buffer returned by oscms_free_octet_buffer and any enclosed data.
     *
     * @param buffer A pointer to the data to copy
     * @param length The number of bytes to copy
     *
     * @return A pointer to the new OscmsOctetBuffer structure or NULL
     */
    SO_EXPORT OscmsOctetBuffer *oscms_octet_buffer_new_from_buffer(const uint8_t *buffer, size_t length);

    /**
     * @brief Initialize an existing OscmsOctetBuffer structure
     *
     * Initializes the specified OscmsOctetBuffer structure to an empty state.
     *
     * @param octet_buffer A pointer to the OscmsOctetBuffer structure to initialize
     *
     * NOTE: Care must be taken NEVER to call this function on a buffer that has already been initialized and
     * contains data. It will result in a memory leak.
     *
     * This function is NULL-safe.
     */
    SO_EXPORT void oscms_octet_buffer_init(OscmsOctetBuffer *octet_buffer);

    /**
     * @brief Create a new OscmsOctetBuffer structure from an array of bytes
     *
     * Initializes the specified OscmsOctetBuffer structure  a copy of the  specified data.
     *
     * Use oscms_empty_octet_buffer to free the buffer any enclosed data.
     *
     * @param octet_buffer A pointer to the OscmsOctetBuffer structure to initialize
     * @param buffer A pointer to the data to copy
     * @param length The number of bytes to copy
     *
     * @return Zero on success, non-zero on failure
     */
    SO_EXPORT int oscms_octet_buffer_init_from_buffer(
        OscmsOctetBuffer *octet_buffer, const uint8_t *buffer, size_t length);

    /**
     * @brief Initializes an OscmsOctetBuffer structure from an array of bytes with tracking
     *
     * Initializes the specified OscmsOctetBuffer structure with  a copy of the specified data.
     *
     * Use oscms_empty_octet_buffer to free the buffer any enclosed data.
     *
     * @param octet_buffer A pointer to the OscmsOctetBuffer structure to initialize
     * @param buffer A pointer to the data to copy
     * @param length The number of bytes to copy
     * @param tracker A an optional pointer to the OscmsSequence structure in which to track the allocated memory
     *
     * @return Zero on success, non-zero on failure
     */
    SO_EXPORT int oscms_octet_buffer_tracked_init_from_buffer(
        OscmsOctetBuffer *octet_buffer, const uint8_t *buffer, size_t length, OscmsSequence *tracker);

    /**
     * @brief Create a new OscmsOctetBuffer structure of a specified size
     *
     * Creates a new, but empty, OscmsOctetBuffer with a pre-allocated buffer of the specified size.
     *
     * The allocated buffer is zeroed.
     *
     * Use oscms_free_octet_buffer to free the buffer returned by oscms_free_octet_buffer and any enclosed data.
     *
     * @param length The number of bytes to allocate
     *
     * @return A pointer to the new OscmsOctetBuffer structure or NULL
     */
    SO_EXPORT OscmsOctetBuffer *oscms_octet_buffer_new_sized(size_t length);

    /**
     * @brief Create a new OscmsOctetBuffer structure from a  C style string
     *
     * Creates a new OscmsOctetBuffer structure initialized with a copy of the
     * specified string. The buffer does NOT include the NUL terminator.
     *
     * Use oscms_free_octet_buffer to free the buffer returned by oscms_free_octet_buffer and any enclosed data.
     *
     * @param cstring A pointer to the string to copy
     *
     * @return A pointer to the new OscmsOctetBuffer structure or NULL
     */
    SO_EXPORT OscmsOctetBuffer *oscms_octet_buffer_new_from_string(const char *cstring);

    /**
     * @brief Duplicate an OscmsOctetBuffer structure into a new instance
     *
     * Creates a new OscmsOctetBuffer structure initialized with a copy of the
     * specified OscmsOctetBuffer structure.
     *
     * Use oscms_free_octet_buffer to free the buffer returned by oscms_free_octet_buffer and any enclosed data.
     *
     * @param octet_buffer A pointer to the OscmsOctetBuffer structure to duplicate
     *
     * @return A pointer to the new OscmsOctetBuffer structure or NULL
     */
    SO_EXPORT OscmsOctetBuffer *oscms_octet_buffer_duplicate(const OscmsOctetBuffer *octet_buffer);

    /**
     * @brief Copy an OscmsOctetBuffer structure into an existing instance
     *
     * Initializes an existing OscmsOctetBuffer structure with a copy of the
     * specified OscmsOctetBuffer structure.
     *
     * Use oscms_empty_octet_buffer to free the enclosed buffer
     *
     * @param source A pointer to the OscmsOctetBuffer structure to copy
     * @param octet_buffer A pointer to the OscmsOctetBuffer structure to initialize
     * @param tracker A opiotnalpointer to the OscmsSequence structure in which to track the allocated memory
     *
     *
     * @return 0 on success
     */
    SO_EXPORT int oscms_octet_buffer_copy(
        const OscmsOctetBuffer *source, OscmsOctetBuffer *octet_buffer, OscmsSequence *tracker);

    /**
     * @brief Free an OscmsOctetBuffer structure
     *
     * Frees an OscmsOctetBuffer structure and any enclosed data.
     *
     * Do NOT call this function if the data enclosed is not dynamically allocated. It ALWAYS assumes
     * that it needs to free any contained buffer.
     *
     * This function is NULL-safe
     *
     * @param octetBuffer A pointer to the OscmsOctetBuffer structure to free
     *
     */
    SO_EXPORT void oscms_free_octet_buffer(OscmsOctetBuffer *octetBuffer);

    /**
     * @brief Empty an OscmsOctetBuffer structure
     *
     * Empties an OscmsOctetBuffer structure by freeing any enclosed data.
     *
     * Do NOT call this function if the data enclosed is not dynamically allocated. It ALWAYS assumes
     * that it needs to free any contained buffer.
     *
     * This function is NULL-safe
     *
     * @param octetBuffer A pointer to the OscmsOctetBuffer structure to empty
     */
    SO_EXPORT void oscms_empty_octet_buffer(OscmsOctetBuffer *octetBuffer);

    /**
     * @brief Compare two OscmsOctetBuffer structures
     *
     * Compares two OscmsOctetBuffer structures for equality of their contents.
     *
     * @param left A pointer to the first OscmsOctetBuffer structure to compare
     * @param right A pointer to the second OscmsOctetBuffer structure to compare
     *
     * * Two NULL pointers will be considered equal, as will two identical pointers
     * * If only one pointer is NULL, their contents will not be considered equal. This includes the case where one is
     *   NULL and the other contains a zero length buffer
     * * If the lengths of the two OscmsOctetBuffer structures are not equal, they will not be considered equal
     * * If the contents of the two OscmsOctetBuffer structures are not equal, they will not be considered equal
     * * If one buffer has a NULL data member and the other does not, the two OscmsOctetBuffer structures will not be
     *   considered equal
     * * If only one buffer has a NULL data member, the two OscmsOctetBuffer structures will not be considered equal
     * * Two zero-length data buffers match
     *
     * @return true if the two OscmsOctetBuffer structures are equivalent, false otherwise
     */
    SO_EXPORT bool oscms_octet_buffer_compare(const OscmsOctetBuffer *left, const OscmsOctetBuffer *right);

    //------------------------------------------------------------------------------
    //
    // The ASN.1  contains the concept of an "OCTET STRING", which is a close analogue of the API's
    // OscmsOctetBuffer structure.
    //
    // These function prototypes are meant to exist in the concrete implementations of the API, as they are generally
    // useful, and should leverage the tracked memory functions in oscms_utilities.h.  They are not part of the exposed
    // API.
    //

    /**
     * @brief Initialize an OscmsOctetBuffer structure from an ASN.1 OCTET STRING
     *
     * Initializes an new  structure initialized with a copy of the provided ASN.1 OCTET STRING.
     *
     * Use oscms_free_octet_buffer to free the buffer returned by oscms_free_octet_buffer and any enclosed data.
     *
     * @param octet_string A pointer to the ASN.1 OCTET STRING to copy
     * @param octet_buffer A pointer to the OscmsOctetBuffer structure to initialize
     * @param tracker A pointer to a memory tracking sequence. If NULL, no memory tracking will occur.
     *
     * @return 0 on success
     */
    int oscms_octet_buffer_init_from_octet_string(
        const void *octet_string_void, OscmsOctetBuffer *octet_buffer, OscmsSequence *tracker);

    /**
     * @brief Initialize an ASN.1 OCTET STRING from an OscmsOctetBuffer structure
     *
     * Initializes an existing structure with a copy of the provided OscmsOctetBuffer.
     *
     * @param octet_buffer A pointer to the OscmsOctetBuffer structure to copy
     * @param octet_string A pointer to the ASN.1 OCTET STRING to initialize
     *
     * return 0 on success
     */
    int oscms_octet_string_init_from_octet_buffer(const OscmsOctetBuffer *octet_buffer, void *octet_string_void);

    /**
     * @brief Initialize an ASN.1 OCTET STRING from a buffer
     *
     * Initializes an existing structure with a copy of the provided buffer.
     *
     * @param buffer A pointer to the buffer to copy
     * @param length The length of the buffer
     * @param octet_string A pointer to the ASN.1 OCTET STRING to initialize
     *
     * return 0 on success
     */
    int oscms_octet_string_init_from_buffer(const uint8_t *buffer, size_t length, void *octet_string_void);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_OCTET_BUFFER_H
