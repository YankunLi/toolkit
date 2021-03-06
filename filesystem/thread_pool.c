#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <memory.h>
#include <time.h>
#include <string.h>
#include <sys/statfs.h>
#include <pthread.h>
#include <assert.h>
#include <malloc.h>
#include <errno.h>

#include "thread_pool.h"

static struct thread_pool_t *tp_ptr = NULL;

extern void destroy_thread_pool()
{}
extern void start_thread_pool(struct thread_pool_t *tp_p) {
    if (tp_p)
        return -1;

    while (!tp_p->tp_stop_pool) {
        if (tp_p->tp_run_count < tp_p->tp_threads_num) {
            err = run_thread(tp_p);
            if 
    }
}

static void entry(struct thread_pool_t *tp_p)
{
    int err;
    int i;
redo:
    for (i = 0; i < tp_p->tp_threads_num; i++) {
        err = pthread_create(&tp_p->tp_thread_array[i].ti_tid,
                NULL, tp_p->tp_work, NULL);
        if (err == EAGAIN)
            goto redo;
        else if (err == 0)
            tp_p->tp_run_count++;
        else
            tp_p->tp_build_thread_errno++;
    }
}

static void *run_thread()
{
}

extern void clear_thread_pool(struct thread_pool_t *tp_p)
{
    if (tp_p->tp_thread_array && tp_p) {
        void *p = (void *) tp_p->tp_thread_array;
        free(p);
    }
}

extern void stop_thread_pool()
{}

extern void pause_thread_pool()
{}

extern void set_thread_work(struct thread_pool_t *tp_p, void (*func)())
{
    if (!tp_p)
        tp_p->tp_work = func;
}

extern int init_thread_pool(struct thread_pool_t *tp_p, int thread_num)
{
    if (thread_num <= 0 || tp_p == NULL)
        return -1;

    if (!tp_ptr->tp_stop_pool) {
        return -1;
    }

    if (tp_ptr) {
        clear_thread_pool(tp_p);
    }

    tp_ptr->tp_max_size = 1024;
    tp_ptr->tp_min_size = 1;
    if (thread_num > tp_ptr->tp_max_size || thread_num < tp_ptr->tp_min_size)
        return -1;

    tp_ptr->tp_threads_num = thread_num;
    tp_ptr->tp_thread_array = (struct thread_info_t *) malloc(
            tp_ptr->tp_threads_num * sizeof(struct thread_info_t));
    if (!tp_ptr->tp_thread_array)
        return -1;
}
