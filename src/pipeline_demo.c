#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int p[2];
    if (pipe(p) == -1) { perror("pipe"); return 1; }

    pid_t pid1 = fork();
    if (pid1 < 0) { perror("fork"); return 1; }
    if (pid1 == 0) {
        // first child: ls > pipe
        dup2(p[1], STDOUT_FILENO);
        close(p[0]); close(p[1]);
        execlp("ls", "ls", (char *)NULL);
        perror("execlp ls");
        _exit(127);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) { perror("fork"); return 1; }
    if (pid2 == 0) {
        // second child: pipe > grep .c
        dup2(p[0], STDIN_FILENO);
        close(p[1]); close(p[0]);
        execlp("grep", "grep", ".c", (char *)NULL);
        perror("execlp grep");
        _exit(127);
    }

    // parent closes both ends and waits
    close(p[0]); close(p[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}
