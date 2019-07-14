# TinyLog

[中文REAMDME请看这里](README_zh-CN.md)

Tinylog is a lightweight C-language high performance log component for UNIX environment, It is high performance, asynchronized, thread-safe and process-safe log library for C/C++.

It support log archiving, asynchronized, multithreading writing, multiprocessing writing, non-blocking mode.  

output example:

```C
[2018-04-03 21:52:13,485][INFO][        example.c:7   ] This is a log message.
```

archive example:  

```C
root@raspberrypi:/home/pi/code/tiny-log/test # ls log/ -l
total 11564
-rw-r----- 1 root root 8754060 Apr 20 21:48 test.log
-rw-r----- 1 root root 1543852 Apr 20 21:48 test.log-20180420-214824.gz
-rw-r----- 1 root root 1539119 Apr 20 21:48 test.log-20180420-214830.gz
```

## Features

1. Log to compressed archive file.
2. Log level output.
3. log format customization.
4. asynchronized log output.
5. Multiple log file support.
6. printf, vprintf similar interface, easy to expand.
7. non-blocking log mode.
8. Multithreading concurrent write.
9. Multiprcessing concurrent write.

## Usage

1. Include the log header file `tlog.h` in the C code.
2. Call `tlog_init` to initialize the log module.
3. Call `tlog` function output log.
4. Call `tlog_exit` to exit the shutdown log component.

## Example

1. Output log

    ```C
    #include <stdio.h>
    #include "tlog.h"

    int main(int argc, char *argv[])
    {
        tlog_init("example.log", 1024 * 1024, 8, 0, 0);
        tlog(TLOG_INFO, "This is a log message.\n");
        tlog_exit();
        return 0;
    }
    ```

1. Independent log stream  

    ```C
    #include <stdio.h>
    #include "tlog.h"

    int main(int argc, char *argv[])
    {
        tlog_log *log = NULL;
        tlog_init("example.log", 1024 * 1024, 8, 0, 0);
        log = tlog_open("another.log", 1024 * 1024, 8, 0, TLOG_SEGMENT);
        tlog_printf(log, "This is a separate log stream\n");
        tlog_close(log);
        tlog_exit();
        return 0;
    }
    ```

If you want filename wihout path in log, you can specify the macro BASE_FILE_NAME as the filename and generate as short file name when compiling. example as follows: (please check makefile in example directory.)  
For makefile:

```C
CFLAGS += -DBASE_FILE_NAME=\"$(notdir $<)\"
```

For cmake:

```C
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DBASE_FILE_NAME='\"$(notdir $<)\"'")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBASE_FILE_NAME='\"$(notdir $<)\"'")
```

## API description

1. int tlog_init(const char *logfile, int maxlogsize, int maxlogcount, int buffsize, unsigned int flag);  
    `Function`：Initialize log module  
    `logfile`: log file  
    `maxlogsize`: The maximum size of a single log file.  
    `maxlogcount`: Number of archived logs.  
    `buffsize`: Buffer size  
    `flag`: log output flag: List of flags are as follows  
    * `TLOG_MULTI_WRITE`: Enable multi-process write single log mode. (Note: When using this mode, the maxlogsize parameter of all processes must be the same)  
    * `TLOG_NOCOMPRESS`: The archive log is not compressed.  
    * `TLOG_SEGMENT`: Log segmentation, used to register the callback function, returns a complete log for subsequent processing.  
    * `TLOG_NONBLOCK`: Do not block when buffer is insufficient.  
    * `TLOG_SCREEN`: Output logs to the screen.  

1. tlog(level, format, ...)  

    `Function`：Print log  
    `level`: Current log Levels  
    `format`: Log formats  

1. tlog_exit（）  

    `Function`：Log component exits  

1. tlog_reg_format_func(tlog_format_func func)  

    `Function`：Registers a custom Format function, and the callback function is defined as：tlog_format_func  

1. tlog_reg_log_output_func(tlog_log_output_func output, void *private)  
    `Function`: Register the custom log output function. The callback function is defined as: tlog_log_output_func. The TLOG_SEGMENT flag can be set during log initialization to return the callback to an independent full log.

1. tlog_setlevel(tlog_level level)  

    `Function`：Set log level，valid level are :TLOG_DEBUG, TLOG_INFO, TLOG_NOTICE, TLOG_WARN, TLOG_ERROR, TLOG_FATAL.

1. tlog_setlogscreen(int enable)  

    `Function`：set whether the log is output to screen.  

1. tlog_open(const char *logfile, int maxlogsize, int maxlogcount, int buffsize, unsigned int flag)  

    `Function`: Initializes a new log stream. When finished, it is closed with tlog_cloese.  
    `logfile`: log file  
    `maxlogsize`: The maximum size of a single log file.  
    `maxlogcount`: The number of archived logs.  
    `buffsize`: The size of the buffer.  
    `flag`: log output flag: List of flags are as follows  
    * `TLOG_MULTI_WRITE`: Enable multi-process write single log mode. (Note: When using this mode, the maxlogsize parameter of all processes must be the same)  
    * `TLOG_NOCOMPRESS`: The archive log is not compressed.  
    * `TLOG_SEGMENT`: Log segmentation, used to register the callback function, returns a complete log for subsequent processing.  
    * `TLOG_NONBLOCK`: Do not block when buffer is insufficient.  
    * `TLOG_SCREEN`: Output logs to the screen.  
    `return value`: log stream handle.  

1. tlog_close(tlog_log *log)  

    `Function`: Turn off the log stream  
    `log`: The log stream handle.  

1. tlog_printf(tlog_log *log, const char *format, ...) 

    `Function`: Print the log to the specified log stream  
    `log`: The log stream handle.  
    `format`: The log format.  

1. tlog_vprintf(tlog_log *log, const char *format, va_list ap)  

    `Function`: Print the log to the specified log stream  
    `log`: The log stream handle.  
    `format`: The log format.  
    `ap`: List of parameters.  

1. tlog_logscreen(tlog_log *log, int enable)  

    `Function`: Set whether the log stream is output to the screen  
    `log`: The log stream handle.  
    `enable`: Whether to enable.  

1. tlog_localtime(struct tlog_time *tm)  

    `Function`: Get local time.  
    `tm`: Local time output.  

1. tlog_reg_output_func(tlog_log *log, tlog_output_func output)  

    `Function`: Register the log stream output callback function. After the specified, the built-in write local file interface will be invalid. The TLOG_SEGMENT flag can be set when the log stream is initialized to return the callback to an independent complete log.

1. tlog_set_private(tlog_log *log, void *private)

    `Function`: Set private parameters for retrieval in the callback function.  
    `log`: The log stream handle.  
    `private`: private parameter.  

1. tlog_get_private(tlog_log *log)  

    `Function`: Get the private parameter, which is obtained from the callback function.  
    `log`: The log stream handle.  
    `return value`: private parameter.  

## License

MIT License
