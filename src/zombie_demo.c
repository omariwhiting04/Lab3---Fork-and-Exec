#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        printf("[child] exiting quickly (pid=%d)\n", getpid());
        _exit(0);
    } else {
        printf("[parent] child=%d exited; sleeping so it becomes a zombie...\n", pid);
        sleep(10);                    // check with: ps -l | grep ' Z '
        waitpid(pid, NULL, 0);        // reap
        printf("[parent] reaped child %d\n", pid);
        return 0;
    }
}
