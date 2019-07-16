#include "tlog.h"
#include <pthread.h>
#include <stdint.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct tlog_log *logs = NULL;

void *test(void *arg)
{
    int id = (intptr_t)arg;
    int i = 0;

    for (i = 0; i < 100000; i++) {
        tlog(TLOG_ERROR, "%d i = %d\n", id, i);
    }
    return NULL;
}

void *test1(void *arg)
{
    int id = (intptr_t)arg;
    int i = 0;

    for (i = 0; i < 100000; i++) {
        tlog_printf(logs, " %d i = %d\n", id, i);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    tlog_init("log/test.log", 1024 * 1024 * 32, 10, 0, 0);
    logs = tlog_open("log/test1.log", 1024 * 1024 * 32, 10, 0, TLOG_NOCOMPRESS);
    pthread_attr_t attr;
    pthread_t threads[10];
    pthread_t threads1[10];
    int i;
    int ret;

    pthread_attr_init(&attr);
    for (i = 0; i < 10; i++) {
        ret = pthread_create(&threads[i], &attr, test, (void *)(intptr_t)i);
        if (ret != 0) {
            return 1;
        }
    }

    for (i = 0; i < 10; i++) {
        ret = pthread_create(&threads1[i], &attr, test1, (void *)(intptr_t)i);
        if (ret != 0) {
            return 1;
        }
    }

    for (i = 0; i < 10; i++) {
        void *retval = NULL;
        pthread_join(threads1[i], &retval);
    }

    for (i = 0; i < 10; i++) {
        void *retval = NULL;
        pthread_join(threads[i], &retval);
    }

    tlog_close(logs);
    tlog_exit();
    return 0;
}