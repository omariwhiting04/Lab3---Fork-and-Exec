#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
    pid_t p=fork(); if(p<0){perror("fork");return 1;}
    if(p==0){ _exit(0); }
    printf("parent: child=%d exited; sleeping so it becomes a zombie...\n",p);
    sleep(10);
    waitpid(p,NULL,0);
    printf("parent: reaped child %d\n",p);
    return 0;
}
