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

#include <cstring>
#include <gtest/gtest.h>

extern "C"
{
#include "oscms_codecs_api/octet_buffer.h"
}

TEST(OctetBuffer, New)
{
    OscmsOctetBuffer *buffer = oscms_octet_buffer_new();
    EXPECT_NE(buffer, nullptr);
    EXPECT_EQ(buffer->data, nullptr);
    EXPECT_EQ(buffer->length, 0);
    oscms_free_octet_buffer(buffer);
}

TEST(OctetBuffer, NewFromBuffer)
{
    uint8_t data[]           = {0x01, 0x02, 0x03, 0x04};
    OscmsOctetBuffer *buffer = oscms_octet_buffer_new_from_buffer(data, sizeof(data));
    EXPECT_NE(buffer, nullptr);
    EXPECT_EQ(buffer->length, sizeof(data));
    EXPECT_EQ(memcmp(buffer->data, data, sizeof(data)), 0);
    oscms_free_octet_buffer(buffer);
}

TEST(OctetBuffer, NewFromString)
{
    const char *str          = "Hello World";
    size_t len               = strlen(str);
    OscmsOctetBuffer *buffer = oscms_octet_buffer_new_from_string(str);
    EXPECT_NE(buffer, nullptr);
    EXPECT_EQ(buffer->length, len);
    EXPECT_EQ(memcmp(buffer->data, str, len), 0);
    oscms_free_octet_buffer(buffer);

    buffer = oscms_octet_buffer_new_from_string(0);
    EXPECT_NE(buffer, nullptr);
    EXPECT_EQ(buffer->length, 0);
    EXPECT_EQ(buffer->data, nullptr);
    oscms_free_octet_buffer(buffer);

    buffer = oscms_octet_buffer_new_from_string("");
    EXPECT_NE(buffer, nullptr);
    EXPECT_EQ(buffer->length, 0);
    EXPECT_EQ(buffer->data, nullptr);
    oscms_free_octet_buffer(buffer);
}

TEST(OctetBuffer, CopySuccess)
{
    uint8_t data[]           = {0x01, 0x02, 0x03, 0x04};
    OscmsOctetBuffer *buffer = oscms_octet_buffer_new_from_buffer(data, sizeof(data));
    ASSERT_NE(buffer, nullptr);

    OscmsOctetBuffer *copy = oscms_octet_buffer_duplicate(buffer);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->length, buffer->length);
    ASSERT_NE(copy->data, nullptr);
    EXPECT_EQ(memcmp(copy->data, buffer->data, buffer->length), 0);
    oscms_free_octet_buffer(copy);
    oscms_free_octet_buffer(buffer);
}

TEST(OctetBuffer, CopyFailure)
{
    OscmsOctetBuffer *buffer = oscms_octet_buffer_duplicate(nullptr);
    EXPECT_EQ(buffer, nullptr);

    buffer = oscms_octet_buffer_new();
    ASSERT_NE(buffer, nullptr);
    OscmsOctetBuffer *copy = oscms_octet_buffer_duplicate(buffer);
    EXPECT_EQ(copy, nullptr);
    oscms_free_octet_buffer(buffer);

    buffer = oscms_octet_buffer_new_from_string("test");
    ASSERT_NE(buffer, nullptr);
    buffer->length = 0; // Set up pathological case where we have data but a zero length
    copy           = oscms_octet_buffer_duplicate(buffer);
    EXPECT_EQ(copy, nullptr);
    oscms_free_octet_buffer(buffer);
}

TEST(OctetBuffer, Free)
{
    // Basically we should be able to call free with all types of NULL data and it should not crash

    // Top level NULL pointer
    oscms_free_octet_buffer(0);

    // Nested NULL pointer
    OscmsOctetBuffer *buffer = oscms_octet_buffer_new();
    oscms_free_octet_buffer(buffer);

    // Valid data
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    buffer         = oscms_octet_buffer_new_from_buffer(data, sizeof(data));
    oscms_free_octet_buffer(buffer);
}

TEST(OctetBuffer, CompareFailure)
{
    OscmsOctetBuffer *buffer1 = oscms_octet_buffer_new();
    ASSERT_NE(buffer1, nullptr);
    OscmsOctetBuffer *buffer2 = oscms_octet_buffer_new_from_string("test");
    ASSERT_NE(buffer2, nullptr);
    OscmsOctetBuffer *buffer3 = oscms_octet_buffer_new_from_string("Test");
    ASSERT_NE(buffer3, nullptr);
    OscmsOctetBuffer *buffer4 = oscms_octet_buffer_new_from_string("Tst");
    ASSERT_NE(buffer4, nullptr);

    EXPECT_FALSE(oscms_octet_buffer_compare(buffer1, nullptr));
    EXPECT_FALSE(oscms_octet_buffer_compare(nullptr, buffer2));

    // Null data in left
    EXPECT_EQ(oscms_octet_buffer_compare(buffer1, buffer2), false);

    // Different lengths
    EXPECT_EQ(oscms_octet_buffer_compare(buffer2, buffer4), false);

    // Different data
    EXPECT_EQ(oscms_octet_buffer_compare(buffer2, buffer3), false);

    oscms_free_octet_buffer(buffer1);
    oscms_free_octet_buffer(buffer2);
    oscms_free_octet_buffer(buffer3);
    oscms_free_octet_buffer(buffer4);
}

TEST(OctetBuffer, CompareSuccess)
{
    // Both NULL - match
    EXPECT_TRUE(oscms_octet_buffer_compare(nullptr, nullptr));

    OscmsOctetBuffer *buffer1 = oscms_octet_buffer_new_from_string("test");
    ASSERT_NE(buffer1, nullptr);
    OscmsOctetBuffer *buffer2 = oscms_octet_buffer_new_from_string("test");
    ASSERT_NE(buffer2, nullptr);

    // Same data contents
    EXPECT_TRUE(oscms_octet_buffer_compare(buffer1, buffer2));
    oscms_free_octet_buffer(buffer1);
    oscms_free_octet_buffer(buffer2);

    // Manufactured cases
    uint8_t *test_string     = (uint8_t *)"test";
    OscmsOctetBuffer buffer3 = {
        .length = 4,
        .data   = test_string,
    };
    OscmsOctetBuffer buffer4 = {
        .length = 4,
        .data   = test_string,
    };

    // Pointing to same location
    EXPECT_TRUE(oscms_octet_buffer_compare(&buffer3, &buffer4));

    buffer3.length = 0;
    buffer4.length = 0;

    // Both zero length
    EXPECT_TRUE(oscms_octet_buffer_compare(&buffer3, &buffer4));
}

TEST(OctetBuffer, Initialize)
{
    OscmsOctetBuffer buffer = {.length = 23, .data = (OscmsOctet *)0xdeadbeef};
    oscms_octet_buffer_init(&buffer);
    EXPECT_EQ(buffer.length, 0);
    EXPECT_EQ(buffer.data, nullptr);

    // Quick check for NULL safety
    oscms_octet_buffer_init(0);
}
