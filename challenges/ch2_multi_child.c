#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s N\n",argv[0]);return 1;}
    int N=atoi(argv[1]);
    for(int i=0;i<N;i++){
        pid_t p=fork(); if(p<0){perror("fork");return 1;}
        if(p==0){ printf("child index=%d pid=%d\n",i,getpid()); _exit(i+1); }
    }
    for(int k=0;k<N;k++){ int st; pid_t c=wait(&st);
        if(WIFEXITED(st)) printf("parent: child %d exited %d\n",c,WEXITSTATUS(st));
    }
    return 0;
}
