Tinylog
==============
Tinylog是一个UNIX环境下轻量级的C语言日志组件，提供了常见的日志输出接口，并日志按一定格式输出到日志文件中。

支持日志归档，支持多线程并发写日志，支持非阻塞日志。

日志输出例子
```
[2018-04-03 21:52:13,485][INFO][        example.c:7   ] This is a log message.
```

特性
--------------
1. 日志压缩归档。
2. 日志级别输出。
3. 日志格式定制。
4. 非阻塞日志。
5. 多线程并发写。

使用
==============
1. 将日志头文件`tlog.h`包含到C代码的中。
2. 调用`tlog_init`初始化日志模块。
3. 调用`tlog`日志输出函数输出日志。
4. 调用`tlog_exit`退出关闭日志组件。

例子
--------------
```c
#include <stdio.h>
#include "tlog.h"

int main(int argc, char *argv[]) 
{
    tlog_init("./", "example.log", 1024 * 1024, 8, 1, 0);
    tlog(TLOG_INFO, "This is a log message.\n");
    tlog_exit();
    return 0;
}
```

如果要让日志中文件名不包含路径，在编译的时候，可指定编译宏BASE_FILE_NAME，在Makefile中可指定如下语句，实现编译时生成短文件名：(例子请参考example的makfile。)  
makefile   
```
%.o : %.c
	$(CC) $(CFLAGS) -DBASE_FILE_NAME=\"$(notdir $<)\" -c $< -o $@
```

cmake   
```
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DBASE_FILE_NAME='\"$(notdir $<)\"'")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBASE_FILE_NAME='\"$(notdir $<)\"'")
```
API说明
----------------
1. int tlog_init(const char *logdir, const char *logname, int maxlogsize, int maxlogcount, int block, int buffsize);    
功能：初始化日志模块  
logdir: 日志输出路径  
logname: 日志名。  
maxlogsize: 单个日志文件最大大小。  
maxlogcount: 归档日志个数。  
block: 缓冲区不足时，是否阻塞。  
buffsize: 缓冲区大小。  

2. tlog(level, format, ...)  
功能：打印日志  
level: 当前日志级别  
format: 日志格式。  

3. tlog_exit（）  
功能：日志组件退出。  

4. tlog_reg_format_func(tlog_format_func func)  
功能：注册自定义格式函数，回调函数定义为：tlog_format_func 

5. tlog_setlevel(tlog_level level)  
功能：设置日志级别，有效参数为TLOG_DBG, TLOG_INFO, TLOG_WARN, TLOG_ERR.  

6. tlog_setlogscreen(int enable)  
功能：设置日志是否输出到屏幕　  
  
License
===============
MIT License


