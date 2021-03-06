/*
 *
 */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/param.h>

int init_daemon(int no_ch_dir, int no_close_fd) {

    signal(SIGHUP ,SIG_IGN);
    signal(SIGTTIN ,SIG_IGN);
    signal(SIGTSTP ,SIG_IGN);
    signal(SIGTTOU ,SIG_IGN);
    //create child process
    int pid = fork();

    //exit parent process
    if (pid < 0 || pid > 0) {
        if (pid < 0)
            return -1;
        exit(0);
    }

    //create new session
    if (setsid() < 0) {
        return -1;
    }

    pid = fork();
    if (pid < 0 || pid > 0) {
        if (pid < 0)
            return -1;
        exit(0);
    }

    int i = 0;
    for (i = 0; i < NOFILE; i++)
        close(i);

    //change directory of work
    if (0 == no_ch_dir) {
        chdir("/");
    }

    //redirection for console
    if (0 == no_close_fd) {
        int fd = open("/dev/null", O_RDWR, 0);
        if (fd < 0)
            return -1;

        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
    }

    umask(0);

    //handle signal
    signal(SIGCHLD, SIG_IGN);

    return 0;
}
