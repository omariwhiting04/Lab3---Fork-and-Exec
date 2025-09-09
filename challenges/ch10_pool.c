#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Usage: ./ch10_pool M task1 task2 task3 ...
   Spawns up to M children at once; each child "processes" a task:
   here we just print start/finish with PID and sleep(1) to simulate work. */

int main(int argc,char**argv){
    if(argc<3){fprintf(stderr,"Usage: %s M task1 [task2 ...]\n",argv[0]);return 1;}
    int M=atoi(argv[1]); if(M<1){fprintf(stderr,"M must be >=1\n");return 1;}
    int running=0, next=2, total=argc-2, done=0; int st;

    while(done<total){
        while(running<M && next<argc){
            pid_t p=fork(); if(p<0){perror("fork");return 1;}
            if(p==0){ printf("start pid=%d task=%s\n",getpid(),argv[next]);
                      sleep(1);
                      printf("finish pid=%d task=%s\n",getpid(),argv[next]);
                      _exit(0); }
            running++; next++;
        }
        pid_t w=wait(&st);
        if(w>0){ running--; done++; }
    }
    return 0;
}
