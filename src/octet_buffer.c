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

#include <stdlib.h>
#include <string.h>

#include "oscms_codecs_api/logging.h"
#include "oscms_codecs_api/octet_buffer.h"
#include "oscms_codecs_api/oscms_utilities.h"

SO_EXPORT void oscms_octet_buffer_init(OscmsOctetBuffer *octet_buffer)
{
    if (octet_buffer)
    {
        octet_buffer->data   = 0;
        octet_buffer->length = 0;
    }
}

SO_EXPORT int oscms_octet_buffer_init_from_buffer(OscmsOctetBuffer *octet_buffer, const uint8_t *buffer, size_t length)
{
    if (!octet_buffer)
    {
        return -1;
    }

    oscms_octet_buffer_init(octet_buffer);

    if (buffer && length > 0)
    {
        octet_buffer->data = malloc(length);
        if (!octet_buffer->data)
        {
            oscms_log(LOG_CRIT, "%s: malloc of %zx bytes failed", __func__, length);
            return -1;
        }
        else
        {
            octet_buffer->length = length;
            (void)memcpy(octet_buffer->data, buffer, length);
        }
    }
    return 0;
}

SO_EXPORT int oscms_octet_buffer_tracked_init_from_buffer(
    OscmsOctetBuffer *octet_buffer, const uint8_t *buffer, size_t length, OscmsSequence *tracker)
{
    if (oscms_octet_buffer_init_from_buffer(octet_buffer, buffer, length) != 0)
    {
        return -1;
    }
    if (tracker && octet_buffer->data)
    {
        if (oscms_track_other(octet_buffer->data, tracker) != 0)
        {
            oscms_empty_octet_buffer(octet_buffer);
            return -1;
        }
    }
    return 0;
}

SO_EXPORT OscmsOctetBuffer *oscms_octet_buffer_new_from_buffer(const uint8_t *buffer, size_t length)
{
    OscmsOctetBuffer *octet_buffer = malloc(sizeof(OscmsOctetBuffer));
    if (octet_buffer)
    {
        if (oscms_octet_buffer_init_from_buffer(octet_buffer, buffer, length) != 0)
        {
            free(octet_buffer);
            return 0;
        }
    }
    return octet_buffer;
}

SO_EXPORT OscmsOctetBuffer *oscms_octet_buffer_new_sized(size_t length)
{
    OscmsOctetBuffer *octet_buffer = malloc(sizeof(OscmsOctetBuffer));
    if (octet_buffer)
    {
        octet_buffer->length = length;
        octet_buffer->data   = 0;

        if (length)
        {
            octet_buffer->data = calloc(1, length);
            if (!octet_buffer->data)
            {
                oscms_log(LOG_CRIT, "%s: calloc failed", __func__);
                free(octet_buffer);
                octet_buffer = 0;
            }
        }
    }
    return octet_buffer;
}

SO_EXPORT OscmsOctetBuffer *oscms_octet_buffer_new_from_string(const char *cstring)
{
    if (!cstring || strlen(cstring) == 0)
    {
        return oscms_octet_buffer_new();
    }

    return oscms_octet_buffer_new_from_buffer((const uint8_t *)cstring, strlen(cstring));
}

SO_EXPORT OscmsOctetBuffer *oscms_octet_buffer_duplicate(const OscmsOctetBuffer *octet_buffer)
{
    if (!octet_buffer || octet_buffer->data == 0 || octet_buffer->length == 0)
    {
        return 0;
    }

    return oscms_octet_buffer_new_from_buffer(octet_buffer->data, octet_buffer->length);
}

SO_EXPORT int oscms_octet_buffer_copy(
    const OscmsOctetBuffer *source, OscmsOctetBuffer *octet_buffer, OscmsSequence *tracker)
{
    if (!source || !octet_buffer || !source->data || source->length == 0)
    {
        return -1;
    }

    return oscms_octet_buffer_tracked_init_from_buffer(octet_buffer, source->data, source->length, tracker);
}

SO_EXPORT OscmsOctetBuffer *oscms_octet_buffer_new(void)
{
    return oscms_octet_buffer_new_from_buffer(NULL, 0);
}

SO_EXPORT void oscms_empty_octet_buffer(OscmsOctetBuffer *octetBuffer)
{
    if (octetBuffer != NULL)
    {
        if (octetBuffer->data)
        {
            // Zeroing the data buffer before freeing.
            // Using explicit_bzero because it is never optimized or removed by
            // the compiler.
            (void)explicit_bzero(octetBuffer->data, octetBuffer->length);

            free(octetBuffer->data);
            octetBuffer->data = 0;
        }
        octetBuffer->length = 0;
    }
}

SO_EXPORT void oscms_free_octet_buffer(OscmsOctetBuffer *octet_buffer)
{
    oscms_empty_octet_buffer(octet_buffer);
    free(octet_buffer); // free() is NULL-safe
}

SO_EXPORT bool oscms_octet_buffer_compare(const OscmsOctetBuffer *left, const OscmsOctetBuffer *right)
{
    // First the obvious case of identity (also catches both NULL)
    if (left == right)
    {
        return true;
    }

    // If only one is NULL, they can't match (we dont' consider a zero lenghth string to be NULL)
    if (!left || !right)
    {
        return false;
    }

    // If the lengths don't match, they can't match
    if (left->length != right->length)
    {
        return false;
    }

    // If they both point to the same data, they match (but this may be a BIG problem if free is ever called on either)
    if (left->data == right->data)
    {
        return true;
    }

    // If only one has data, they can't match
    if (!left->data || !right->data)
    {
        return false;
    }

    // We know the lengths are the same. Zero length buffers match
    if (left->length == 0)
    {
        return true;
    }

    // Otherwise, check the data
    return memcmp(left->data, right->data, left->length) == 0;
}
