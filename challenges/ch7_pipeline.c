#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s \"pattern\"\n",argv[0]);return 1;}
    int p[2]; if(pipe(p)==-1){perror("pipe");return 1;}
    pid_t c1=fork(); if(c1<0){perror("fork");return 1;}
    if(c1==0){ dup2(p[1],STDOUT_FILENO); close(p[0]); close(p[1]);
               execlp("ls","ls",(char*)NULL); perror("execlp ls"); _exit(127); }
    pid_t c2=fork(); if(c2<0){perror("fork");return 1;}
    if(c2==0){ dup2(p[0],STDIN_FILENO); close(p[1]); close(p[0]);
               execlp("grep","grep",argv[1],(char*)NULL); perror("execlp grep"); _exit(127); }
    close(p[0]); close(p[1]); waitpid(c1,NULL,0); waitpid(c2,NULL,0); return 0;
}
