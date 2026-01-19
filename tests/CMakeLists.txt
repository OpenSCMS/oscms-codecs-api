# Copyright (c) 2025 LG Electronics, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
# http:#www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.
#
# SPDX-License-Identifier: Apache-2.0

file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable(api_tests ${SOURCES})

target_link_libraries(api_tests oscms_api_common GTest::gtest_main gmock_main)
target_include_directories(api_tests
                           PRIVATE ${PROJECT_SOURCE_DIR}/include/public)

add_test(NAME api_tests COMMAND api_tests)

# file(GLOB TEST_JSON CONFIGURE_DEPENDS "*.json") file(GLOB TEST_CSV
# CONFIGURE_DEPENDS "*.csv") file(GLOB TEST_TXT CONFIGURE_DEPENDS "*.txt")

# foreach(TEST_FILE ${TEST_JSON} ${TEST_CSV} ${TEST_TXT}) cmake_path(GET
# TEST_FILE FILENAME TEST_BASENAME) message(STATUS "Configuring TEST FILE:
# ${TEST_BASENAME}") configure_file(${TEST_BASENAME} ${TEST_BASENAME} COPYONLY)
# endforeach()

gtest_discover_tests(api_tests)
