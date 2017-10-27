#include <stdio.h>
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
#include <sys/stat.h>

#define PATH "/var/lib/ceph/osd/ceph-1/"
#define file_path(file_name) PATH#file_name

void generate_random_str(char *buf, int length)
{
    int i;
    char char_array[] = "abcdefghijklmnopqrstuvwxyzAQWERTYUIOPLKJHGFDSZXCVBNM1234567890-_";
    srand((unsigned) time(NULL));

    for (i = 0; i < length - 1; i++) {
        buf[i] = char_array[rand() % 64];
    }

    buf[length-1] = '\0';

    return;
}

struct info_thread_t {
    pthread_t it_tid;
};

struct  pool_thread_t {
    struct info_thread_t *pt_array;
    int pt_run_count;
    int pt_max_size;
    int pt_min_size;
    int pt_threads_num;
    int pt_build_thread_error;

    void (*pt_start) (struct pool_thread_t *);
    void (*pt_stop) (struct pool_thread_t *);
    void (*pt_wait) (struct pool_thread_t *);
    void * (*pt_run_thread) ();
    void (*pt_init) (struct pool_thread_t *, int);
    void (*pt_destroy) (struct pool_thread_t *);
};

void work(long t_id)
{
    int sum = 0;
    while (1) {
        sum = 2*2*2;
    }
//    char content_byte[4096 * 16];
//    int fd;
//    char file_name[32];
//    char path_name[128];
//    unsigned long long total_size;
//    struct statfs disk_info;
//    int parent_path_length;
//    int ret;
//
//   // strcpy(path_name, PATH);
//    snprintf(path_name, 64, "%s%ld/\0", PATH, t_id);
//    parent_path_length = strlen(path_name);
//    memset(content_byte, '0', 4096 * 16);
//    mkdir(path_name, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
//
//redo:
//    statfs(PATH, &disk_info);
//    total_size = disk_info.f_bsize * disk_info.f_bfree;
//    total_size = total_size >> 30;
//
//    if (total_size < 5)
//        goto out;
//
//    path_name[parent_path_length] = '\0';
//    generate_random_str(file_name, 32);
//    strcat(path_name, file_name);
//
//    fd = open(path_name, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
//
//    ret = write(fd, content_byte, sizeof(content_byte));
//    fsync(fd);
//    //fdatasync(fd);
//
//    close(fd);
//
//    goto redo;
//
//out:
//    return;
}

void entry()
{
    pthread_t tid;
    tid = pthread_self();

    work(tid);
}

void destroy_thread_pool(struct pool_thread_t *p_info)
{

}

void start_pool(struct pool_thread_t *p_info)
{
    int err;
    int i;

    for (i = 0; i < p_info->pt_threads_num; i++) {
redo:
        err = pthread_create(&p_info->pt_array[i].it_tid,
                NULL, p_info->pt_run_thread, NULL);
        if (err == EAGAIN)
            goto redo;
        else if (err == 0) {
            p_info->pt_run_count++;
        }
        else
            p_info->pt_build_thread_error++;

    }

    return;
}

void * run_thread()
{
    entry();
}

void stop_thread_pool(struct pool_thread_t *p_info)
{}

void wait_threads(struct pool_thread_t *p_info)
{}

void init_thread_pool(struct pool_thread_t *p_info, int thread_num)
{
    if (thread_num <= 0 || p_info->pt_max_size < p_info->pt_min_size
            || p_info->pt_min_size <= 0)
                assert(0);

    if (thread_num > p_info->pt_max_size) {
        thread_num = p_info->pt_max_size;
    }
    p_info->pt_threads_num = thread_num;

    p_info->pt_run_count = 0;
    p_info->pt_build_thread_error = 0;

    void *p = malloc(sizeof(struct info_thread_t) * thread_num);

    if (NULL != p)
        p_info->pt_array = (struct info_thread_t *) p;
    else
        assert(0);

    int i;
    for (i = 0; i < p_info->pt_threads_num; i++) {
        p_info->pt_array[i].it_tid = 0;
    }

    return;
}

struct pool_thread_t g_tpool_info = {
    .pt_run_count = 0,
    .pt_max_size = 1000,
    .pt_min_size = 1,
    .pt_threads_num = 0,

    .pt_start = start_pool,
    .pt_stop = stop_thread_pool,
    .pt_wait = wait_threads,
    .pt_run_thread = run_thread,
    .pt_init = init_thread_pool,
    .pt_destroy = destroy_thread_pool,
};

int main(int argc, char *argv[])
{
    g_tpool_info.pt_init(&g_tpool_info, 1000);
    g_tpool_info.pt_start(&g_tpool_info);
    sleep(10000);
    return 0;
}
