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