/*
 * Author: Yankun Li <lioveni99@gmail.com>
 *
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

#define CHUNCK_SIZE 4096

static long long max_size;
static int block_size;
static int fd;
static int old_size;

#define FAILURE_RETRY(expression) ({ \
    typeof(expression) __ret = 0;                  \
    do {                          \
        __ret = expression;         \
    } while (-1 == __ret && errno == EINTR); \
     __ret; \
     })

static void _close();

static int _open_file(char *path, int mode)
{
    int flags, ret;

    flags = O_RDWR|O_CREAT;
    fd = FAILURE_RETRY(open(path, flags, 0644));
    if (fd < 0) {
        int err = errno;
        return -err;
    }

    struct stat st;
    ret = fstat(fd, &st);
    if (ret) {
        ret = errno;
        fprintf(stderr, "fstat failure to call %s", path);
        ret = -ret;
        goto out_fd;
    }

    old_size = st.st_size;
    block_size = st.st_blksize;

    return ret;
out_fd:
    _close();
    return -ret;
}

static void _close()
{
    FAILURE_RETRY(close(fd));
}

static int fill_file(int off, int chunck)
{
    int ret = 0;
    char *buf;
    int page_size;

    page_size = getpagesize();

    ret = posix_memalign((void**)&buf, page_size, chunck);
    if (ret) {
        return -ret;
    }

    memset((void *)buf, 0, chunck);

    int i = off;
    for (; i + chunck <= max_size; i += chunck) {
        ret = pwrite(fd, (void *)buf, chunck, i);
        if (ret < 0) {
            free(buf);
            return ret;
        }
    }

    if (i < max_size) {
        ret = pwrite(fd, (void *)buf, max_size - i, i);
        if (ret < 0) {
            free(buf);
            return ret;
        }
    }

    return 0;
}

extern int resize_file(char *path, int size, int fill)
{
    int ret;
    int mode = 0644;

    max_size = size;
    ret = _open_file(path, mode);
    if (ret < 0) {
        fprintf(stderr, "_open_file unable to open file %s", path);
        return -ret;
    }

/*    ret = fstat(fd, &st);
    if (ret) {
        ret = errno;
        fprintf(stderr, "unable to fstat %s file", path);
        ret = -ret;
        goto out_fd;
    } */
    if (max_size < old_size) {
        fprintf(stderr, "Currently, The size of file is %d <  %d, some data will be lost",
                old_size, size);
    }

    ret = ftruncate(fd, size);
    if (ret < 0) {
        ret = errno;
        fprintf(stderr, "Unable to invoke ftruncat for %d", fd);
        ret = -ret;
        goto out_fd;
    }

    ret = posix_fallocate(fd, 0, size);
    if (ret) {
        fprintf(stderr, "Unable to allocate space for %d", fd);
        ret = -errno;
        goto out_fd;
    }

    if (fill && old_size < size) {
        ret = fill_file(old_size, CHUNCK_SIZE);
        if (ret) {
            fprintf(stderr, "Unable to fill extra space");
        }
    }

    _close();

    return ret;

out_fd:
    _close();
    return ret;

}

