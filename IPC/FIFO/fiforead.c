#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const char *fifo_name = "/tmp/fifo";
    int pipe_fd = -1;
    int data_fd = -1;
    int res = 0;
    char buffer[PIPE_BUF + 1];
    int read_bytes = 0;
    int write_bytes = 0;

    memset(buffer, '\0', sizeof(buffer));
    printf("Process %d opening FIFO O_RDONLY\n", getpid());

    pipe_fd = open(fifo_name, O_RDONLY);
    data_fd = open("DataFormFIFO.txt", O_WRONLY | O_CREAT, 0644);
    printf("Process %d result %d\n", getpid(), pipe_fd);

    if (pipe_fd != -1) {
        int tmp_send_bytes = 0;
        read_bytes = read(pipe_fd, buffer, PIPE_BUF);
        if (read_bytes < 0) {
            fprintf(stderr, "Read error %d \n", getpid());
            exit(EXIT_FAILURE);
        }
        while (read_bytes > 0) {
redo:
            res = write(data_fd, &buffer[tmp_send_bytes], read_bytes);
            if (res < read_bytes) {
                read_bytes -= res;
                tmp_send_bytes += res;
                goto redo;
            }
            tmp_send_bytes = 0;
            read_bytes = read(pipe_fd, buffer, PIPE_BUF);
        }
        close(pipe_fd);
        close(data_fd);
    } else {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

