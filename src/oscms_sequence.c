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

#include "oscms_codecs_api/oscms_sequence.h"
#include "oscms_codecs_api/logging.h"

SO_EXPORT void oscms_sequence_init(OscmsSequence *sequence)
{
    if (sequence)
    {
        sequence->allocated_size = 0;
        sequence->count          = 0;
        sequence->data           = 0;
    }
}

SO_EXPORT void oscms_free_sequence(OscmsSequence *sequence)
{
    oscms_empty_sequence(sequence);
    free(sequence);
}

SO_EXPORT void oscms_empty_sequence(OscmsSequence *sequence)
{
    if (!sequence)
        return;

    for (size_t i = 0; i < sequence->count; i++)
    {
        free(sequence->data[i]), sequence->data[i] = 0;
    }

    free(sequence->data), sequence->data = 0;
    oscms_sequence_init(sequence);
}

SO_EXPORT int oscms_sequence_add(OscmsSequence *sequence, void *data)
{
    if (!sequence)
        return -1;

    if (sequence->count == sequence->allocated_size)
    {
        size_t new_size = sequence->allocated_size ? sequence->allocated_size * 2 : 16;
        void **old_data = sequence->data; // In case of failure

        // If the data pointer is NULL, reallocarray will perform an inital allocation.
        sequence->data = (void **)reallocarray(sequence->data, new_size, sizeof(void *));

        if (!sequence->data)
        {
            sequence->data = old_data;
            oscms_log(LOG_CRIT, "%s: reallocarray failed to allocated %zu entries", __func__, new_size);
            return -1;
        }
        sequence->allocated_size = new_size;
    }

    sequence->data[sequence->count++] = data;
    return 0;
}

SO_EXPORT int oscms_sequence_foreach(
    const OscmsSequence *sequence, OscmsSequenceIteratorCallback callback, void *user_data)
{
    if (!sequence)
        return -1;

    // Calling with a NULL callback is allowed, though pointless
    for (size_t i = 0; i < sequence->count && callback; i++)
    {
        int ret = callback(sequence->data[i], user_data);
        if (ret)
            return ret;
    }
    return 0;
}
