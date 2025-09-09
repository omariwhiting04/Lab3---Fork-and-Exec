#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
    pid_t a=fork(); if(a<0){perror("fork");return 1;}
    if(a==0){ execl("/bin/echo","echo","one","two",(char*)NULL); perror("execl"); _exit(1); }
    pid_t b=fork(); if(b<0){perror("fork");return 1;}
    if(b==0){ char* argv[]={(char*)"echo",(char*)"one",(char*)"two",NULL};
              execv("/bin/echo",argv); perror("execv"); _exit(1); }
    waitpid(a,NULL,0); waitpid(b,NULL,0); return 0;
}
