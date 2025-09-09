#include <stdio.h>
#include <stdlib.h>
extern char **environ;
int main(int argc,char**argv){
    const char* my=getenv("MYVAR");
    printf("worker:"); for(int i=0;i<argc;i++) printf(" %s",argv[i]);
    if(my) printf("  MYVAR=%s",my);
    printf("\n"); return 0;
}
