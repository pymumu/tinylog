#include "tlog.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    tlog_log *log = NULL;

    /* init and output log message */
    tlog_init("example.log", 1024 * 1024, 8, 1, 0, 0, 1);
    tlog(TLOG_INFO, "This is a log message.\n");

    /* open another log file, and output message*/
    log = tlog_open("another.log", 1024 * 1024, 8, 1, 0, 0, 1);
    tlog_printf(log, "This is a separate log stream\n");
    /* close log stream */
    tlog_close(log);

    /* flush pending message, and exit tlog */
    tlog_exit();
    return 0;
}
