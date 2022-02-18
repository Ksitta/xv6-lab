#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void){
    int pid;
    int p[2];
    char buf[10];
    pipe(p);
    if(fork() == 0){
        pid = getpid();
        if(read(p[0], buf, 1) == 0){
            fprintf(2, "fail to read from parent\n");
            exit(1);
        }
        printf("%d: received ping\n", pid);
        write(p[1], buf, 1);
    }else{
        pid = getpid();
        buf[0] = 'a';
        write(p[1], buf, 1);
        if(read(p[0], buf, 1) == 0){
            fprintf(2, "fail to read from child\n");
            exit(1);
        }
        printf("%d: received pong\n", pid);
    }
    close(p[0]);
    close(p[1]);
    exit(0);
}