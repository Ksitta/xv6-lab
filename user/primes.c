#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void new_pro(int p[2]){
    int prime;
    int n;
    read(p[0], &prime, 4);
    printf("prime %d\n", prime);
    if(read(p[0], &n, 4) == 0){
        close(p[0]);
        exit(0);
    }
    int new_p[2];
    pipe(new_p);
    if(fork()){
        close(new_p[1]);
        new_pro(new_p);
        close(new_p[0]);
    }else{
        close(new_p[0]);
        do{
            if(n % prime){
                write(new_p[1], &n, 4);
            }
        } while(read(p[0], &n, 4));
        close(new_p[1]);
        wait(0);
    }
    exit(0);
}

int main(void){
    int i;
    int pip[2];
    pipe(pip);
    for(i = 2; i <= 35; i++){
        write(pip[1], &i, 4);
    }
    close(pip[1]);
    new_pro(pip);
    close(pip[0]);
    wait(0);
    exit(0);
    return 0;
}