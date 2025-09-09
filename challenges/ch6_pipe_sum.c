#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
    int fd[2]; if(pipe(fd)==-1){perror("pipe");return 1;}
    pid_t p=fork(); if(p<0){perror("fork");return 1;}
    if(p==0){
        close(fd[1]); FILE* in=fdopen(fd[0],"r");
        long x,sum=0; while(fscanf(in,"%ld",&x)==1) sum+=x;
        printf("Sum = %ld\n",sum); fclose(in); _exit(0);
    }else{
        close(fd[0]); FILE* out=fdopen(fd[1],"w");
        for(int i=1;i<=10;i++) fprintf(out,"%d ",i);
        fclose(out); waitpid(p,NULL,0); return 0;
    }
}
