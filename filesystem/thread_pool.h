#ifndef _H_THREAD_POOL_H_
#define _H_THREAD_POOL_H_

struct thread_info_t {
    pthread_t ti_tid;
};

struct thread_pool_t {
    struct thread_info_t *tp_thread_array;
    int tp_run_count;
    int tp_max_size;
    int tp_min_size;
    int tp_threads_num;
    int tp_build_thread_errno;
    int tp_stop_pool;
    unsigned long tp_loop_interval;

    void (*tp_work)();
};


extern void entry();
extern void destroy_thread_pool();
extern void start_thread_pool();
static void *run_thread();
extern void clear_thread_pool();
extern void stop_thread_pool();
extern void pause_thread_pool();
extern int init_thread_pool();


#endif
