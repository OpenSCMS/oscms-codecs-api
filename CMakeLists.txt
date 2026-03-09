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

cmake_minimum_required(VERSION 3.28.3)
project(
  OscmsApi
  DESCRIPTION "OpenSCMS Codecs Abstract API"
  VERSION 1.0.0
  LANGUAGES C CXX) # CXX added for testing support

include(FetchContent)
FetchContent_Declare(
  oscms_cmake_helpers
  GIT_REPOSITORY https://github.com/OpenSCMS/oscms-cmake-helpers.git
  GIT_TAG main)
FetchContent_MakeAvailable(oscms_cmake_helpers)

oscms_enable_cppcheck()
oscms_enable_testing()

# add source files
file(GLOB SOURCES "src/*.c" CMAKE_CONFIGURE_DEPENDS)

# Build an object library for the common API code to be used by concrete
# implementations
add_library(oscms_api_common STATIC ${SOURCES})
target_include_directories(oscms_api_common PUBLIC "include/public")
target_compile_options(
  oscms_api_common
  PRIVATE -Wall
          -Wextra
          --pedantic
          -fPIC
          $<IF:$<CONFIG:Debug>,-O0,-O2>
          $<IF:$<CONFIG:Debug>,-g,>
          -fvisibility=hidden
          -Werror
          -Wno-unused-function
          -Wno-missing-field-initializers)

if(RUN_CPPCHECK)
  message(STATUS "Adding cppcheck custom command")
  # we use a custom command to ensure that cppcheck is run after the build, sees
  # all the source files at once, and stops the build if there are errors
  add_custom_command(
    TARGET oscms_api_common
    POST_BUILD
    COMMAND
      "${CPPCHECK}" ARGS "${CPPCHECK_OPTIONS}"
      "$<JOIN:$<TARGET_PROPERTY:oscms_api_common,INCLUDE_DIRECTORIES>,;-I>"
      ${SOURCES}
    COMMENT "Running cppcheck"
    COMMAND_EXPAND_LISTS)
endif()

if(BUILD_TESTS)
  # Bring in the Unit tests
  add_subdirectory(tests)
endif()
