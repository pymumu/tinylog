Tiny-Log
==============

[中文REAMDME请看这里](README_zh-CN.md)

Tiny-log is a lightweight C-language log component for UNIX environment that provides a common log output interface and logs output to a file in certain format.

Support for log archiving, multithreading writing, non-blocking mode.  

Features
--------------
1. Log compressed archive.
2. Log level output.
3. log format customization.
4. non-blocking log.
5. Multithreading concurrent write.

Usage
==============
1. Include the log header file `tlog.h` in the C code.
2. Call `tlog_init` to initialize the log module.
3. Call log output function output log.
4. Call `tlog_exit` to exit the shutdown log component.

Example
--------------
```c
#include <stdio.h>
#include "tlog.h"

int main(int argc, char *argv[])
{
    int i = 0;
    tlog_init("./", "example.log", 1024 * 1024, 8, 1, 0);
    for (i = 0; i < 100; i++) {
        tlog(TLOG_INFO, "i = %d\n", i);
    }
    tlog_exit();
}
```

API description
----------------
1. int tlog_init(const char *logdir, const char *logname, int maxlogsize, int maxlogcount, int block, int buffsize);    
Function：Initialize log module  
logdir: Log Output path.    
logname: Log name.  
maxlogsize: The maximum size of a single log file.    
maxlogcount: Number of archived logs.    
block: Blocked if buffer is not sufficient.    
buffsize: Buffer size  

2. tlog(level, format, ...)  
Function：Print log   
level: Current log Levels  
format: Log formats    

3. tlog_exit（）  
Function：Log component exits    

4. tlog_reg_format_func(tlog_format_func func)  
Function：Registers a custom Format function, and the callback function is defined as：tlog_format_func  
  
License
===============
MIT License


