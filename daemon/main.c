/*
 *
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "daemon.h"

int parse_arg()
{}

void release_resources()
{}

int main(int argc, char *argv[])
{
    //parse parameter
    parse_arg();

    //init for daemon
    init_daemon(0, 0);

    int fd = open("/tmp/daemon.log", O_RDWR|O_CREAT|O_APPEND);
    write(fd, "first entry\n", 12);

    char buf[1024];
    int count = 0;

    while (1) {
        count++;
        if (10 < count)
            break;

        snprintf(buf, 1024, "number: %d, runtime log\n", count);
        write(fd, buf, strlen(buf));
//        if (count % 2 == 0)
//            fsync(fd);
        sleep(2);
    }

    close(fd);

    release_resources();

    return 0;
}
