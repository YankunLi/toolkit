#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const char *fifo_name = "/tmp/fifo";
    int data_fd = -1;
    int pipe_fd = -1;
    int res = 0;
    int bytes_sent = 0;
    char buffer[PIPE_BUF + 1];

    memset(buffer, '\0', sizeof(buffer));
    if (access(fifo_name, F_OK) == -1) {
        res = mkfifo(fifo_name, 0777);
        if (res != 0) {
            fprintf(stderr, "Could not create fifo %s\n", fifo_name);
            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d opening FIFO O_WRONLY\n", getpid());
    pipe_fd = open(fifo_name, O_WRONLY);
    data_fd = open("Data.txt", O_RDONLY);
    printf("Process %d result %d\n", getpid(), pipe_fd);

    if (pipe_fd != -1) {
        int bytes_read = 0;
        bytes_read = read(data_fd, buffer, PIPE_BUF);
        int temp_write_bytes = 0;
        while (bytes_read > 0) {
redo:
            res = write(pipe_fd, &buffer[temp_write_bytes], bytes_read);
            if (res == -1) {
                fprintf(stderr, "Write error on pipe \n");
                exit(EXIT_FAILURE);
            }
            bytes_sent += res;
            if (bytes_read > res) {
                bytes_read -= res;
                temp_write_bytes += res;
                goto redo;
            }
            temp_write_bytes = 0;
            bytes_read = read(data_fd, buffer, PIPE_BUF);
            buffer[bytes_read] = '\n';
        }

        close(data_fd);
        close(pipe_fd);
    } else
        exit(EXIT_FAILURE);

    printf("Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);
}

