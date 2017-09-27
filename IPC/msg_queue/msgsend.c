#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_TEXT 512

struct user {
    char name[20];
    int age;
};

struct msg_st {
    long int msg_type;
    char user[MAX_TEXT];
};

int main(int argc, char *argv[])
{
    int running = 1;
    struct msg_st data;
    char buffer[BUFSIZ];
    int msgid = -1;
    struct user us = {
        .age = 12,
        .name = "liyankun"
    };
    char * u_ptr = (char *) &us;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid ==-1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while (running) {
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);
        data.msg_type = 2;
        //strcpy(data.user, u_ptr);
        memcpy((void *)data.user, (void*)u_ptr, sizeof(struct user));

        if (msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1) {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }

        if (strncmp(buffer, "end", 3) == 0)
            running = 0;
        sleep(4);
    }

    exit(EXIT_SUCCESS);
}
