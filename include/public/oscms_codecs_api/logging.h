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

#ifndef OSCMS_CODECS_LOGGING_H
#define OSCMS_CODECS_LOGGING_H

#include <stdarg.h>
#include <syslog.h> // For logging priorities

#include "so_export.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    /**
     * @file logging.h
     * @brief Provide a simple logging interface for use throughout the library
     *
     * If no logging function is provided, via oscms_log_set_logger
     * messages will be logged to stderr by default.
     *
     * Only logs written to syslog will be formatted with meta-information such
     * as timestamps and process id. All other logs will be formatted according
     * to the provided format string.
     *
     * The logging level provided to the initialization functions is only used
     * when logging to either stdout or stderr. Logs to the system logger are
     * always logged regardless of the logging level.
     *
     * When logging to the system log, the caller is responsible for opening and
     * closing the connection to the system logger.
     */

    typedef void (*oscms_log_function_ptr)(int level, const char *fmt, va_list args);

    /**
     * Initialize the logging system by providing a custom logging function.
     *
     * @param func The custom logging function to use. It must have the same signature as vprintf() or vsyslog().
     * @param log_level The minimum log level to log. Must be one of the LOG_* values.
     *
     * If no logging function is provided, messages will be logged to stderr by default.
     * If func is NULL, logging will be set to stderr with a level of LOG_INFO.
     */
    SO_EXPORT void oscms_log_set_logger(oscms_log_function_ptr func, int log_level);

    /**
     * Log a message with the given log level and format string.
     *
     * @param level The log level, as described by the syslog() priority levels
     * @param fmt The format string, as described by printf()
     * @param ... The arguments to the format string
     *
     * This function is marked with the GCC format attribute, which means that the
     * compiler will check the format string against the arguments at compile time.
     *
     * This function does not return a value, but does return when finished.
     */
    SO_EXPORT __attribute__((format(printf, 2, 3))) void oscms_log(int level, const char *fmt, ...);

    /**
     * Log a message with the given log level and format string using a va_list.
     *
     * @param level The log level, as described by the syslog() priority levels.
     * @param fmt The format string, as described by printf().
     * @param args The arguments to the format string provided as a va_list.
     *
     * This function allows for logging with a va_list, facilitating variable
     * argument logging. It does not return a value, but completes the logging
     * operation when finished.
     *
     * The primary use of this function is to pass it to other libraries
     * that use the va_list interface.
     */
    void oscms_vlog(int level, const char *fmt, va_list args);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // OSCMS_CODECS_LOGGING_H
