#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int data_processed = 0;
    int pipes[2];
    const char data[] = "123";
    pid_t pid;

    if (pipe(pipes) == 0) {
        pid = fork();
        if (pid == -1) {
            fprintf(stderr, "Fork failure!\n");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            close(0);
            dup(pipes[0]);
            close(pipes[0]);
            close(pipes[1]);
            sleep(1);
            execlp("od", "od", "-c", 0);
            exit(EXIT_FAILURE);
        } else {
            close(pipes[0]);
            data_processed = write(pipes[1], data, strlen(data));
            close(pipes[1]);
            printf("%d - Wrote %d bytes\n", getpid(), data_processed);
        }
    }
    exit(EXIT_FAILURE);
}
