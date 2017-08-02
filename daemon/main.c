/*
 *
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

    FILE *fd = fopen("/tmp/deamon.log", "rw");
    int count = 0;
    while (1) {
        count++;
        if (100 < count)
            break;
        sleep(2);
        fprintf(fd, "number: %d, runtime log", count);
    }

    release_resources();

    return 0;
}
