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
 * @file oscms_sequence.h
 *
 * This file contains the definition of the OscmsSequence type and associated functions
 *
 * The OscmsSequence is a loose analog to the SEQUENCE OF type in ASN.1. It is a dynamic array
 * of pointers to dynamically allocated data.
 *
 * The above is important. Whilst the OscmsSequence can be initialized with a static array and/or the
 * pointers may refrence static memory, the OscmsSequence is not responsible for freeing this memory.
 * Do NOT free the memory used by the OscmsSequence by calling either oscms_empty_sequence or oscms_free_sequence
 * as these always assume that botht the enclosed array, and the pointers stored in the array need to be freed.
 *
 */
#ifndef OSCMS_SEQUENCE_H
#define OSCMS_SEQUENCE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

#include "oscms_codecs_api/so_export.h"

    /**
     * @typedef OscmsSequenceIteratorCallback
     *
     * This is a callback function which is called for each entry in the OscmsSequence.
     *
     * @param data The data pointer stored in the OscmsSequence
     * @param user_data The user data pointer passed to the iterator
     *
     * @return 0 on success, -1 on failure
     *
     * A non-zero return value will terminate the iteration.
     */
    typedef int (*OscmsSequenceIteratorCallback)(void *data, void *user_data);

    /**
     * @struct oscms_sequence_t
     *
     * This represents a basic dynamic array of pointers, which can be used to represent
     * most of the SEQUENCE OF types in the ASN.1 specifications.
     *
     * The array will grow dynamically as entries are added. There is no facility for deleting
     * entries or re-ordering them.
     */
    typedef struct OscmsSequence
    {
        size_t allocated_size; // Number of poitners which can be stored in the allocated array
        size_t count;          // Number of poitners currently stored in the array
        void **data;           // Dynamically allocated buffer.
    } OscmsSequence;

    /**
     * Initializes the OscmsSequence structure to an empty state
     *
     * @param sequence The OscmsSequence structure to initialize
     *
     */
    SO_EXPORT void oscms_sequence_init(OscmsSequence *sequence);

    /**
     * Frees the memory used by the OscmsSequence structure as well as the sequence
     *
     * @param sequence The OscmsSequence structure to free
     *
     * Free all memory used by the OscmsSequence structure and the pointers stored
     * in the array as well as the strucutre  itself.
     *
     */
    SO_EXPORT void oscms_free_sequence(OscmsSequence *sequence);

    /**
     * Frees the memory used by the  OscmsSequence structure
     *
     * @param sequence The OscmsSequence structure to free
     *
     * Free all memory used by the OscmsSequence structure and the pointers stored
     * in the array, but not the actual structure.
     */
    SO_EXPORT void oscms_empty_sequence(OscmsSequence *sequence);

    /**
     * Adds a new pointer to the OscmsSequence structure
     *
     * @param sequence The OscmsSequence structure to add to
     * @param data The pointer to add
     *
     * @return 0 on success, -1 on failure
     */
    SO_EXPORT int oscms_sequence_add(OscmsSequence *sequence, void *data);

    /**
     * Iterates over the OscmsSequence structure, calling the callback function for each entry
     *
     * @param sequence The OscmsSequence structure to iterate over
     * @param callback The callback function to call for each entry
     * @param user_data The user data pointer to pass to the callback function
     *
     * @return 0 on success, -1 on failure
     */
    SO_EXPORT int oscms_sequence_foreach(
        const OscmsSequence *sequence, OscmsSequenceIteratorCallback callback, void *user_data);
#ifdef __cplusplus
}
#endif //__cplusplus
#endif // OSCMS_SEQUENCE_H
