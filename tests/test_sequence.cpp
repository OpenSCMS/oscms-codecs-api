// Copyright(c) 2025 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0(the "License"); you may not
// use this file except in compliance with the License.You may obtain a copy of
// the License at
//
// http : //www.apache.org / licenses / LICENSE - 2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.See the
// License for the specific language governing permissions and limitations under
// the License.
//
// SPDX - License - Identifier : Apache - 2.0

#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

extern "C"
{
#include "oscms_codecs_api/oscms_sequence.h"
}

TEST(OscmsSequenceAll, Null)
{
    OscmsSequence seq = {.allocated_size = 1024, .count = 22, .data = (void **)42};

    oscms_sequence_init(nullptr);
    oscms_free_sequence(nullptr);
    oscms_empty_sequence(nullptr);
    int rc = oscms_sequence_add(nullptr, nullptr);
    ASSERT_NE(0, rc);

    oscms_sequence_foreach(nullptr, nullptr, nullptr);

    rc = oscms_sequence_foreach(&seq, nullptr, nullptr);
    ASSERT_EQ(0, rc);
}

TEST(OscmsSequenceInit, Success)
{
    OscmsSequence seq = {.allocated_size = 1024, .count = 22, .data = (void **)42};
    oscms_sequence_init(&seq);
    ASSERT_EQ(0, seq.count);
    ASSERT_EQ(0, seq.allocated_size);
    ASSERT_EQ(nullptr, seq.data);
}

TEST(OscmsSequenceFree, Success)
{
    OscmsSequence seq;
    oscms_sequence_init(&seq);
    int rc = oscms_sequence_add(&seq, nullptr);
    ASSERT_EQ(0, rc);

    ASSERT_EQ(1, seq.count);
    ASSERT_NE(0, seq.allocated_size);
    ASSERT_NE(nullptr, seq.data);

    oscms_empty_sequence(&seq);
    ASSERT_EQ(0, seq.count);
    ASSERT_EQ(0, seq.allocated_size);
    ASSERT_EQ(nullptr, seq.data);
}

TEST(OscmsSequenceFreeAll, SuccessNullData)
{
    OscmsSequence seq;
    oscms_sequence_init(&seq);
    int rc = oscms_sequence_add(&seq, nullptr);
    ASSERT_EQ(0, rc);
    rc = oscms_sequence_add(&seq, nullptr);
    ASSERT_EQ(0, rc);

    ASSERT_EQ(2, seq.count);
    ASSERT_NE(0, seq.allocated_size);
    ASSERT_NE(nullptr, seq.data);

    oscms_empty_sequence(&seq);
    ASSERT_EQ(0, seq.count);
    ASSERT_EQ(0, seq.allocated_size);
    ASSERT_EQ(nullptr, seq.data);
}

TEST(OscmsSequenceFreeAll, SuccessWithData)
{
    OscmsSequence seq;
    oscms_sequence_init(&seq);

    void *some_data = malloc(16);

    int rc = oscms_sequence_add(&seq, some_data);
    ASSERT_EQ(0, rc);
    ASSERT_EQ(1, seq.count);
    ASSERT_NE(0, seq.allocated_size);
    ASSERT_NE(nullptr, seq.data);
    ASSERT_EQ(some_data, seq.data[0]);

    oscms_empty_sequence(&seq);
    ASSERT_EQ(0, seq.count);
    ASSERT_EQ(0, seq.allocated_size);
    ASSERT_EQ(nullptr, seq.data);
}

TEST(OscmsSequenceAdd, Success)
{
    OscmsSequence seq;
    oscms_sequence_init(&seq);
    ASSERT_EQ(0, seq.count);
    ASSERT_EQ(0, seq.allocated_size);
    ASSERT_EQ(nullptr, seq.data);

    char *some_data = (char *)malloc(16);
    ASSERT_EQ(0, oscms_sequence_add(&seq, some_data));
    ASSERT_NE(nullptr, seq.data);
    EXPECT_EQ(1, seq.count);
    EXPECT_NE(0, seq.allocated_size);
    EXPECT_EQ(some_data, seq.data[0]);

    oscms_empty_sequence(&seq);
    ASSERT_EQ(0, seq.count);
    ASSERT_EQ(0, seq.allocated_size);
    ASSERT_EQ(nullptr, seq.data);
}

static int callback(void *data, void *user_data)
{
    int *callback_count = (int *)user_data;
    *callback_count += 1;
    return 0;
};

TEST(OscmsSequenceForeach, Success)
{
    int callback_count = 0;

    OscmsSequence seq;
    oscms_sequence_init(&seq);
    ASSERT_EQ(0, seq.count);
    ASSERT_EQ(0, seq.allocated_size);
    ASSERT_EQ(nullptr, seq.data);

    ASSERT_EQ(0, oscms_sequence_add(&seq, malloc(8)));
    ASSERT_EQ(0, oscms_sequence_add(&seq, malloc(8)));
    ASSERT_EQ(0, oscms_sequence_add(&seq, malloc(8)));
    ASSERT_NE(nullptr, seq.data);
    EXPECT_EQ(3, seq.count);
    EXPECT_NE(0, seq.allocated_size);

    int rc = oscms_sequence_foreach(&seq, &callback, (void *)&callback_count);
    EXPECT_EQ(0, rc);
    EXPECT_EQ(3, callback_count);

    oscms_empty_sequence(&seq);
    ASSERT_EQ(0, seq.count);
    ASSERT_EQ(0, seq.allocated_size);
    ASSERT_EQ(nullptr, seq.data);
}
