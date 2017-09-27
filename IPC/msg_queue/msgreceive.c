#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

struct user {
    char name[20];
    int age;
};

struct msg_st {
    long int msg_type;
    char user[BUFSIZ];
};
//struct msg_st {
//    long int msg_type;
//    char text[BUFSIZ];
//};

int main(int argc, char *argv[])
{
    int running = 1;
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 2;
    struct user us;
    char *u_ptr = (char *)&us;
    struct user *user_ptr = NULL;


    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while (running) {
        if (msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0) == -1) {
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }

        printf("You wrote: %s\n", data.user);
        //strncpy(u_ptr, data.user, sizeof(struct user));
        memcpy((void *)u_ptr, (void *)data.user, sizeof(struct user));
        if (strncmp(data.user, "end", 3) == 0)
            running = 0;
        user_ptr = (struct user *)u_ptr;
        printf("user name : %s, age is: %d\n", user_ptr->name, user_ptr->age);
    }

    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}


