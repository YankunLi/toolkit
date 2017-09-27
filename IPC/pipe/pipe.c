#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int data_processed = 0;
    int filedes[2];
    const char data[] = "Hello pipe!";

    char buffer[BUFSIZ + 1];
    pid_t pid;

    memset(buffer, 0, sizeof(buffer));
    if (pipe(filedes) == 0) {
        pid = fork();
        if (pid == -1) {
            fprintf(stderr, "fork failure");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            close(filedes[1]);
            data_processed = write(filedes[1], data, strlen(data));
            data_processed = read(filedes[0], buffer, BUFSIZ);
            printf("Read %d bytes: %s\n", data_processed, buffer);
            exit(EXIT_SUCCESS);
        } else {
            close(filedes[0]);
            data_processed = write(filedes[1], data, strlen(data));
            printf("Wrote %d bytesx: %s\n", data_processed, data);
            //sleep(2);
            exit(EXIT_SUCCESS);
        }
    }
    exit(EXIT_SUCCESS);
}
