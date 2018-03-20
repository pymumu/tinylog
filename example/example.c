#include <stdio.h>
#include "tlog.h"

int main(int argc, char *argv[]) 
{
    tlog_init("./", "example.log", 1024 * 1024, 8, 1, 0);
    tlog(TLOG_INFO, "This is a log message.\n");
    tlog_exit();
}
