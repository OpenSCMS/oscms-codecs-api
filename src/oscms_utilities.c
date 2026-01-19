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

#include "oscms_codecs_api/oscms_utilities.h"
#include "oscms_codecs_api/logging.h"

SO_EXPORT void *oscms_tracked_malloc(size_t size, OscmsSequence *tracker)
{
    if (size == 0)
    {
        oscms_log(LOG_CRIT, "%s: Cannot allocate 0 bytes of memory", __func__);
        return NULL;
    }

    void *ptr = calloc(1, size);
    if (ptr)
    {
        if (tracker)
        {
            int rc = oscms_sequence_add(tracker, ptr);
            if (rc != 0)
            {
                // Failed to add to the cache
                oscms_log(LOG_CRIT, "%s: Failed to add allocated memory to the cache", __func__);
                free(ptr);
                ptr = NULL;
            }
        }
    }
    else
    {
        // Failed to allocate memory
        oscms_log(LOG_CRIT, "%s: Failed to allocate %zu bytes of memory", __func__, size);
    }
    return ptr;
}

SO_EXPORT void *oscms_tracked_calloc(size_t count, size_t size, OscmsSequence *tracker)
{
    if (size == 0 || count == 0)
    {
        oscms_log(LOG_CRIT, "%s: Cannot allocate 0 bytes of memory", __func__);
        return NULL;
    }

    if (SIZE_MAX / size < count)
    {
        // Overflow
        oscms_log(LOG_CRIT, "%s: Overflow allocating %zu element(s)s of %zu bytes each", __func__, count, size);
        return NULL;
    }

    void *ptr = calloc(count, size);
    if (ptr)
    {
        if (tracker)
        {
            int rc = oscms_sequence_add(tracker, ptr);
            if (rc != 0)
            {
                // Failed to add to the cache
                oscms_log(LOG_CRIT, "%s: Failed to add allocated memory to the cache", __func__);
                free(ptr);
                ptr = NULL;
            }
        }
    }
    else
    {
        // Failed to allocate memory
        oscms_log(LOG_CRIT, "%s: Failed to allocate %zu bytes of memory", __func__, size * count);
    }
    return ptr;
}

SO_EXPORT int oscms_track_other(void *ptr, OscmsSequence *tracker)
{
    int rc = oscms_sequence_add(tracker, ptr);
    if (rc != 0)
    {
        // Failed to add to the cache
        oscms_log(LOG_CRIT, "%s: Failed to add allocated memory to the cache", __func__);
        return -1;
    }
    return 0;
}
