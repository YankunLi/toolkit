#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *read_fp = NULL;
    FILE *write_fp =  NULL;
    char buffer[BUFSIZ + 1];
    int chars_read = 0;

    memset(buffer, 0, sizeof(buffer));

    read_fp = popen("ls -l", "r");
    write_fp = popen("grep ll", "w");

    if (read_fp && write_fp) {
        chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
        while (chars_read > 0) {
            buffer[chars_read] = '\0';
            fwrite(buffer, sizeof(char), chars_read, write_fp);

            chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
        }
        pclose(read_fp);
        pclose(write_fp);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}
