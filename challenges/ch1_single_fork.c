#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
    pid_t pid=fork(); if(pid<0){perror("fork");return 1;}
    if(pid==0){ printf("Hello from child (PID=%d, PPID=%d)\n",getpid(),getppid()); sleep(2); _exit(7); }
    int st; waitpid(pid,&st,0);
    if(WIFEXITED(st)) printf("Parent: child %d exited with status %d\n",pid,WEXITSTATUS(st));
    return 0;
}
