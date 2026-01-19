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
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <syslog.h>

#include "oscms_codecs_api/logging.h"

#define DEFAULT_LOG_LEVEL LOG_INFO

static const char *const oscms_log_level_strings[] = {
    "emerg", "alert", "crit", "err", "warning", "notice", "info", "debug"};

static int logging_level = DEFAULT_LOG_LEVEL;

static void log_to_syslog(int level, const char *fmt, va_list args)
{
    (void)vsyslog(level, fmt, args);
}

static void log_to_stderr(int level, const char *fmt, va_list args)
{
    if (level > logging_level || !fmt)
        return;

    bool valid_level = level >= LOG_EMERG && level <= LOG_DEBUG;

    (void)fprintf(stderr, "oscms-api [%s]: ", valid_level ? oscms_log_level_strings[level] : "unknown");
    (void)vfprintf(stderr, fmt, args);
    (void)fprintf(stderr, "\n");
}

// Logging function in use. Default to stderr
//
// Declared here to avoid having to provide forward declarations
// of our canned loggers.
static oscms_log_function_ptr logger = log_to_stderr;

SO_EXPORT void oscms_log_set_logger(oscms_log_function_ptr func, int log_level)
{
    logger = func ? func : log_to_stderr;

    // Sanitize log level
    logging_level = (log_level < LOG_EMERG || log_level > LOG_DEBUG) ? DEFAULT_LOG_LEVEL : log_level;
}

SO_EXPORT void oscms_vlog(int level, const char *fmt, va_list args)
{
    if (!logger || !fmt)
        return;

    logger(level, fmt, args);
}

__attribute__((format(printf, 2, 3))) void oscms_log(int level, const char *fmt, ...)
{
    if (!logger || !fmt)
        return;

    va_list args;
    va_start(args, fmt);
    logger(level, fmt, args);
    va_end(args);
}
