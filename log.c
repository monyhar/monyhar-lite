/*
 * This file is originally part of the SLOWProxy
 * (https://github.com/nicholascw/SLOWProxy).
 *
 * Copyright (C) 2020-2021 Nicholas Wang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "log.h"

static loglevel_t setted_lvl = ERR;
static const char *colors[] = {"\x1b[0;32m", "\x1b[1;36m", "\x1b[1;30m",
                               "\x1b[1;33m", "\x1b[1;31m", "\x1b[0m"};

void slow_print_log(loglevel_t lvl, const char *func_name,
                    const char *err_string, const char *src_name,
                    const unsigned int lineno) {
  if (lvl < setted_lvl || setted_lvl == 5) return;
  char str_lvl[25];
  switch (lvl) {
    case DBG:
      snprintf(str_lvl, sizeof(str_lvl), "%s[Debug]%s", colors[DBG], colors[5]);
      break;
    case INFO:
      snprintf(str_lvl, sizeof(str_lvl), "%s[Info]%s", colors[INFO], colors[5]);
      break;
    case WARN:
      snprintf(str_lvl, sizeof(str_lvl), "%s[Warn]%s", colors[WARN], colors[5]);
      break;
    case ERR:
      snprintf(str_lvl, sizeof(str_lvl), "%s[Error]%s", colors[ERR], colors[5]);
      break;
    default:
      snprintf(str_lvl, sizeof(str_lvl), "%s[Panic]%s", colors[ERR], colors[5]);
  }

  time_t t = time(NULL);
  struct tm curr_tm;
  if (!localtime_r(&t, &curr_tm)) perror("localtime_r()");
  char str_time[30];
  str_time[29] = '\0';
  if (!strftime((char *)&str_time, sizeof(str_time), "%FT%T%z", &curr_tm))
    fprintf(stderr, "strftime() failed.\n");
  //[Debug] 2020-07-08 03:27:36 CDT
  (setted_lvl != DBG)
      ? fprintf(stderr, "%s\t%s%s%s: %s(): %s\n", str_lvl, colors[0], str_time,
                colors[5], func_name, err_string)
      : fprintf(stderr, "%s\t%s%s%s: %s:%d: %s(): %s\n", str_lvl, colors[0],
                str_time, colors[5], src_name, lineno, func_name, err_string);
}

void slow_perror_log(const char *func_name, const char *src_name,
                     const unsigned int lineno) {
  /*char str_errno[128];
  str_errno[127] = '\0';
  if(strerror_r(errno, str_errno, 127)!=0) perror("slow_perror_log()");
  else slow_print_log(ERR, func_name, str_errno, src_name, lineno);*/
  slow_print_log(ERR, func_name, strerror(errno), src_name, lineno);
}

loglevel_t slow_loglevel(loglevel_t level) {
  if (level != INVALID) setted_lvl = level;
  return setted_lvl;
}
