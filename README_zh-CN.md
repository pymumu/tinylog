
# Tinylog

Tinylog是一个UNIX环境下轻量级的C/C++高性能异步日志组件，其提供了高性能，异步，线程安全，进程安全的日志功能。

支持日志归档，支持多线程并发写日志，多进程并发写日志，支持非阻塞日志。

日志输出例子

```c
[2018-04-03 21:52:13,485][ INFO][        example.c:7   ] This is a log message.
```

归档目录例子

```c
root@raspberrypi:/home/pi/code/tiny-log/test # ls log/ -l
total 11564
-rw-r----- 1 root root 8754060 Apr 20 21:48 test.log
-rw-r----- 1 root root 1543852 Apr 20 21:48 test.log-20180420-214824.gz
-rw-r----- 1 root root 1539119 Apr 20 21:48 test.log-20180420-214830.gz
```

## 特性

1. 日志压缩归档。
2. 日志级别输出。
3. 日志格式定制。
4. 异步日志输出。
5. 多日志文件支持。
6. printf,vprintf类似接口，易于扩展。
7. 非阻塞日志。
8. 多线程并发写。
9. 多进程并发写。
10. c++流风格日志输出。

## 使用

1. 将日志头文件`tlog.h`包含到C代码的中。
2. 调用`tlog_init`初始化日志模块。
3. 调用`tlog`或`tlog_[debug|info|notice|warn|error|fatal]`日志输出函数输出日志。
4. c++使用cout风格输出日志到`tlog_info`。
5. 调用`tlog_exit`退出关闭日志组件。

## 例子

1. 输出日志

    ```c
    #include <stdio.h>
    #include "tlog.h"

    int main(int argc, char *argv[])
    {
        tlog_init("example.log", 1024 * 1024, 8, 0, 0);
        tlog(TLOG_INFO, "This is a log message.\n");
        tlog_info("This is another log message.\n");
        tlog_exit();
        return 0;
    }
    ```

1. c++流日志

    ```cpp
    #include <stdio.h>
    #include "tlog.h"

    int main(int argc, char *argv[])
    {
        tlog_init("example.log", 1024 * 1024, 8, 0, 0);
        tlog_info << "This is a c++ cout style log message.\n";
        tlog_exit();
        return 0;
    }
    ```

1. 独立日志流

    c printf风格  

    ```c
    #include <stdio.h>
    #include "tlog.h"

    int main(int argc, char *argv[])
    {
        tlog_log *log = NULL;
        tlog_init("example.log", 1024 * 1024, 8, 0, 0);
        log = tlog_open("another.log", 1024 * 1024, 8, 0, TLOG_SEGMENT);
        tlog_printf(log, "This is a separate log stream.\n");
        tlog_close(log);
        tlog_exit();
        return 0;
    }
    ```

    c++ std::out 风格

    ```cpp
    #include <stdio.h>
    #include "tlog.h"

    int main(int argc, char *argv[])
    {
        tlog_log *log = NULL;
        tlog_init("example.log", 1024 * 1024, 8, 0, 0);
        log = tlog_open("another.log", 1024 * 1024, 8, 0, TLOG_SEGMENT);
        tlog_out(log) << "This is a separate log stream.\n";
        tlog_close(log);
        tlog_exit();
        return 0;
    }
    ```

## API说明

1. int tlog_init(const char *logfile, int maxlogsize, int maxlogcount, int buffsize, unsigned int flag);  

    `功能`: 初始化日志模块  
    `logfile`: 日志文件。  
    `maxlogsize`: 单个日志文件最大大小。  
    `maxlogcount`: 归档日志个数。  
    `buffsize`: 缓冲区大小。  
    `flag`:日志输出模式：可设置：  
    * `TLOG_MULTI_WRITE`: 启用多进程写单个日志模式. (注意: 当使用此模式时，所有进程的maxlogsize参数必须一样)  
    * `TLOG_NOCOMPRESS`: 归档日志不进行压缩。  
    * `TLOG_SEGMENT`: 日志分段，用于注册回调函数后，返回一条完整的日志用于后续处理。  
    * `TLOG_NONBLOCK`: 缓冲区不足时，不阻塞。  
    * `TLOG_SCREEN`: 输出日志到屏幕。  
    * `TLOG_SUPPORT_FORK`: 支持fork运行的进程。

1. tlog(level, format, ...)  

    `功能`: 打印日志  
    `level`: 当前日志级别  
    `format`: 日志格式。  

1. tlog_debug, tlog_info, tlog_notice, tlog_warn, tlog_error, tlog_fatal  

    `功能`: 打印日志, c++使用`<<`输出日志。
    `format`: 日志格式。  

1. tlog_exit（）  

    `功能`: 日志组件退出。  

1. tlog_reg_format_func(tlog_format_func func)  

    `功能`: 注册自定义格式函数，回调函数定义为: tlog_format_func  

1. int tlog_reg_log_output_func(tlog_log_output_func output, void *private)
    `功能`: 注册自定义日志输出函数，回调函数定义为：tlog_log_output_func， 可在日志初始化时设置TLOG_SEGMENT标志使回调返回一条独立完整日志。

1. tlog_setlevel(tlog_level level)  

    `功能`: 设置日志级别，有效参数为TLOG_DEBUG, TLOG_INFO, TLOG_NOTICE, TLOG_WARN, TLOG_ERROR, TLOG_FATAL  

1. tlog_getlevel(tlog_level level)  

    `功能`: 获取设置的日志级别。  

1. tlog_set_logfile(const char *logfile)

    `功能`: 设置日志文件。
    `logfile`: 日志文件。  

1. tlog_setlogscreen(int enable)  

    `功能`: 设置日志是否输出到屏幕。  
    `enable`: 是否启用。  
  
1. tlog_open(const char *logfile, int maxlogsize, int maxlogcount, int buffsize, unsigned int flag);  

    `功能`: 　初始化一个新的日志流，完成后，使用tlog_cloese关闭。  
    `logfile`: 日志文件。  
    `maxlogsize`: 单个日志文件最大大小。  
    `maxlogcount`: 归档日志个数。  
    `buffsize`: 缓冲区大小。  
    `flag`:日志输出模式：可设置：  
    * `TLOG_MULTI_WRITE`: 启用多进程写单个日志模式. (注意: 当使用此模式时，所有进程的maxlogsize参数必须一样)  
    * `TLOG_NOCOMPRESS`: 归档日志不进行压缩。  
    * `TLOG_SEGMENT`: 日志分段，用于注册回调函数后，返回一条完整的日志用于后续处理。  
    * `TLOG_NOBLOCK`: 缓冲区不足时，不阻塞。  
    * `TLOG_SCREEN`: 输出日志到屏幕。  
    `返回值`: 日志流句柄。

1. tlog_close(tlog_log *log)  

    `功能`: 关闭日志流。  
    `log`: 日志流句柄。  

1. tlog_printf(tlog_log *log, const char *format, ...)  

    `功能`: 打印日志到指定日志流  
    `log`: 日志流句柄。  
    `format`: 日志格式。  

1. tlog_out(tlog_log *log)  

    `功能`: c++风格打印日志到指定日志流，使用`<<`输出日志  
    `log`: 日志流句柄。  

1. tlog_vprintf(tlog_log *log, const char *format, va_list ap)  

    `功能`: 打印日志到指定日志流  
    `log`: 日志流句柄。  
    `format`: 日志格式。  
    `ap`: 参数列表。  

1. tlog_logscreen(tlog_log *log, int enable)  

    `功能`: 设置日志流是否输出到屏幕  
    `log`: 日志流句柄。  
    `enable`: 是否启用。  

1. tlog_localtime(struct tlog_time *tm)  

    `功能`: 获取本地时间。  
    `tm`: 本地时间输出。  

1. int tlog_reg_output_func(tlog_log *log, tlog_output_func output)  

    `功能`: 注册日志流输出回调函数，指定后，内置的写本地文件接口将失效; 可在日志流初始化时设置TLOG_SEGMENT标志使回调返回一条独立完整日志。  

1. void tlog_set_private(tlog_log *log, void *private)  

    `功能`: 设置私有参数，供回调函数中获取。  
    `log`: 日志流句柄。  
    `private`: 私有参数。  

1. void tlog_get_private(tlog_log *log)

    `功能`: 获取私有参数，供回调函数中获取。  
    `log`: 日志流句柄。  
    `返回值`: 私有参数。  

1. tlog_rename_logfile(tlog_log *log, const char *logfile)

    `功能`: 重命名日志文件。  
    `log`: 日志流句柄。  
    `logfile`: 日志文件。  

## License

MIT License
