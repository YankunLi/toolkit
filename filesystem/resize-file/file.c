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

#define FAILURE_RETRY(expression) ({ \
    typeof(expression) __ret = 0;                  \
    do {                          \
        ret = expression;         \
    } while (-1 == ret && errno == EINTR); \
     __ret; \
     })

static long long max_size;
static int block_size;
static int fd;

static void _close();

extern int resize_file(char *path, int size, int fill)
{

}

static int _open_file(char *path, int mode)
{
    int flags, ret;

    flags = O_RDWR|O_CREAT;
    fd = FAILURE_RETRY(open(path, flags, 0644));
    if (fd < 0) {
        int err = errno;
        fprintf(stderr, "_open_file unable to open file %s", path);
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

    max_size = st.st_size;
    block_size = st.st_blksize;

    return ret;
out_fd:
    _close();
    return -ret;
}

static void _close()
{

}

static int fill_file(int off, int chunck)
{

}
