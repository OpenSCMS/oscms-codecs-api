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

#include <gtest/gtest.h>

#include "oscms_codecs_api/oscms_utilities.h"

TEST(OscmsTrackedMallocTest, ZeroLength)
{
    EXPECT_EQ(oscms_tracked_malloc(0, 0), nullptr);
}

TEST(OscmsTrackedMallocTest, MallocFailure)
{
    EXPECT_EQ(oscms_tracked_malloc(SIZE_MAX, 0), nullptr);
}

TEST(OscmsTrackedMallocTest, MallocSuccess)
{
    void *ptr = oscms_tracked_malloc(1024, 0);
    EXPECT_NE(ptr, nullptr);
    free(ptr);
}

TEST(OscmsTrackedCallocTest, ZeroLength)
{
    EXPECT_EQ(oscms_tracked_calloc(0, 1024, 0), nullptr);
    EXPECT_EQ(oscms_tracked_calloc(1024, 0, 0), nullptr);
}

TEST(OscmsTrackedCallocTest, Overflow)
{
    EXPECT_EQ(oscms_tracked_calloc(SIZE_MAX, 2, 0), nullptr);
    EXPECT_EQ(oscms_tracked_calloc(2, SIZE_MAX, 0), nullptr);
}

TEST(OscmsTrackedCallocTest, CallocFailure)
{
    EXPECT_EQ(oscms_tracked_calloc(1, SIZE_MAX, 0), nullptr);
}

TEST(OscmsTrackedCallocTest, CallocSuccess)
{
    void *ptr = oscms_tracked_calloc(3, 1024, 0);
    EXPECT_NE(ptr, nullptr);
    free(ptr);
}