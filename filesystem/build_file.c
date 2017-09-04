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

int main(int argc, char *argv[])
{
    char content_byte[4094];
    int fd;
    char file_name[32];
    char path_name[64];
    unsigned long long total_size;
    struct statfs disk_info;

    strcpy(path_name, PATH);
    memset(content_byte, '0', 4096);

redo:
    statfs(PATH, &disk_info);
    total_size = disk_info.f_bsize * disk_info.f_bfree;
    total_size = total_size >> 30;

    if (total_size < 5)
        goto out;

    path_name[sizeof(PATH) - 1] = '\0';
    generate_random_str(file_name, 32);
    strcat(path_name, file_name);

    fd = open(path_name, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    write(fd, content_byte, sizeof(content_byte));

    close(fd);

    goto redo;

out:
    return 0;
}
