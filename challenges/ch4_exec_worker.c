#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
    pid_t p=fork(); if(p<0){perror("fork");return 1;}
    if(p==0){
        char* const envp[]={(char*)"MYVAR=hello",NULL};
        char* const argv[]={(char*)"worker",(char*)"arg1",(char*)"arg2",NULL};
        execle("./worker","worker","arg1","arg2",NULL,envp); perror("execle"); _exit(1);
    }
    waitpid(p,NULL,0); return 0;
}
