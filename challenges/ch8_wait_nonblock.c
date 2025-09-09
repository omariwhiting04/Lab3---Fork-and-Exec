#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
    pid_t kids[3]; int secs[3]={1,2,3};
    for(int i=0;i<3;i++){ pid_t p=fork(); if(p==0){ sleep(secs[i]); _exit(100+i); }
                           kids[i]=p; }
    int finished=0, st; while(finished<3){
        pid_t w=waitpid(-1,&st,WNOHANG);
        if(w>0){ if(WIFEXITED(st)) printf("child %d done status %d\n",w,WEXITSTATUS(st));
                 finished++; }
        else if(w==0){ printf("polling...\n"); usleep(200*1000); }
        else { perror("waitpid"); break; }
    }
    return 0;
}
