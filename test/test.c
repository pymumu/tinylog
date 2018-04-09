#include "tlog.h"
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void *test(void *arg)
{
    int id = (int)arg;
    int i = 0;

    for (i = 0; i < 100000; i++) {
        tlog(TLOG_ERR, "%d i = %d\n", id, i);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    tlog_init("./log", "test.log", 1024 * 1024 * 32, 10, 1, 0);
    tlog_setmultiwriter(1);
    pthread_attr_t attr;
    pthread_t threads[10];
    int i;
    int ret;
    pthread_attr_init(&attr);
    for (i = 0; i < 10; i++) {
        ret = pthread_create(&threads[i], &attr, test, (void *)(int)i);
        if (ret != 0) {
            return 1;
        }
    }

    for (i = 0; i < 10; i++) {
        void *retval = NULL;
        pthread_join(threads[i], &retval);
    }

    tlog_exit();
    return 0;
}