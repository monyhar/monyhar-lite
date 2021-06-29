#pragma once
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "dbg.h"  // https://github.com/eerimoq/dbg-macro

static char slow_snprintf_buf[1024];

#define __FNAME__ \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define L_DEBUG(STR) \
  (slow_print_log(DBG, __FUNCTION__, (STR), (__FNAME__), __LINE__));
#define L_INFO(STR) \
  (slow_print_log(INFO, __FUNCTION__, (STR), (__FNAME__), __LINE__));
#define L_WARN(STR) \
  (slow_print_log(WARN, __FUNCTION__, (STR), (__FNAME__), __LINE__));
#define L_ERR(STR) \
  (slow_print_log(ERR, __FUNCTION__, (STR), (__FNAME__), __LINE__));
#define L_PERROR() (slow_perror_log(__FUNCTION__, (__FNAME__), __LINE__));

#define L_DEBUGF(FMT, ...)                                 \
  do {                                                     \
    snprintf(slow_snprintf_buf, 1024, (FMT), __VA_ARGS__); \
    L_DEBUG(slow_snprintf_buf);                            \
  } while (0);
#define L_INFOF(FMT, ...)                                  \
  do {                                                     \
    snprintf(slow_snprintf_buf, 1024, (FMT), __VA_ARGS__); \
    L_INFO(slow_snprintf_buf);                             \
  } while (0);
#define L_WARNF(FMT, ...)                                  \
  do {                                                     \
    snprintf(slow_snprintf_buf, 1024, (FMT), __VA_ARGS__); \
    L_WARN(slow_snprintf_buf);                             \
  } while (0);
#define L_ERRF(FMT, ...)                                   \
  do {                                                     \
    snprintf(slow_snprintf_buf, 1024, (FMT), __VA_ARGS__); \
    L_ERR(slow_snprintf_buf);                              \
  } while (0);

typedef enum {
  DBG = 1,
  INFO = 2,
  WARN = 3,
  ERR = 4,
  SHUT = 5,
  INVALID = -1
} loglevel_t;

void slow_print_log(loglevel_t lvl, const char *func_name,
                    const char *err_string, const char *src_name,
                    const unsigned int lineno);

void slow_perror_log(const char *func_name, const char *src_name,
                     const unsigned int lineno);

loglevel_t slow_loglevel(loglevel_t level);
