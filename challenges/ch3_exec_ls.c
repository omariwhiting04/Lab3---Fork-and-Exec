#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
    pid_t p=fork(); if(p<0){perror("fork");return 1;}
    if(p==0){ execlp("ls","ls","-la",(char*)NULL); perror("execlp"); _exit(1); }
    waitpid(p,NULL,0); printf("parent: child finished\n"); return 0;
}
