/*
 * Copyright (C) 2018 Ruilin Peng (Nick) <pymumu@gmail.com>
 */

#ifndef TLOG_H
#define TLOG_H
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

typedef enum {
    TLOG_DBG = 0,
    TLOG_INFO = 1,
    TLOG_WARN = 2,
    TLOG_ERR = 3,
    TLOG_END = 4
} tlog_level;

struct tlog_time {
    int year;
    int mon;
    int mday;
    int hour;
    int min;
    int sec;
    int millisec;
};

struct tlog_info {
    const char *level;
    const char *file;
    const char *func;
    int line;
    struct tlog_time time;
};

#define tlog(level, format, ...) tlog_ext(level, __FILE__, __LINE__, __func__, 0, format, ##__VA_ARGS__)

extern int tlog_vext(tlog_level level, const char *file, int line, const char *func, void *userptr, const char *format, va_list ap);

extern int tlog_ext(tlog_level level, const char *file, int line, const char *func, void *userptr, const char *format, ...);

extern int tlog_init(const char *logdir, const char *logname, int maxlogsize, int maxlogcount, int block, int buffsize);

extern void tlog_exit(void);

typedef int (*tlog_format_func)(char *buff, int maxlen, struct tlog_info *info, void *userptr, const char *format, va_list ap);
extern int tlog_reg_format_func(tlog_format_func func);

#ifdef __cplusplus
}
#endif /*__cplusplus */
#endif // !TLOG_H
