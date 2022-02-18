#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    char *new_argv[32];
    char argv_array[32][16];
    int raw_num;
    for(raw_num = 0; raw_num < argc - 1; raw_num++){
        new_argv[raw_num] = argv_array[raw_num];
        strcpy(new_argv[raw_num], argv[raw_num + 1]);
    }
    char temp[2];
    char buf[16];
    int pos = 0;
    int arg_pos = raw_num;
    while(1){
        if(read(0, temp, 1) == 0){
            break;
        }
        if(temp[0] == '\n'){
            buf[pos] = '\0';
            if(pos == 0){
                new_argv[arg_pos] = 0;
            }else{
                new_argv[arg_pos] = argv_array[arg_pos];
                strcpy(new_argv[arg_pos], buf);
                new_argv[arg_pos + 1] = 0;
            }
            if(fork()){
                wait(0);
            }else{
                exec(new_argv[0], new_argv);
            }
            arg_pos = raw_num;
            pos = 0;
            continue;
        }
        if(temp[0] == ' '){
            buf[pos] = '\0';
            new_argv[arg_pos] = argv_array[arg_pos];
            strcpy(new_argv[arg_pos], buf);
            arg_pos++;
            pos = 0;
            continue;    
        }
        buf[pos] = temp[0];
        pos++;
    }

    exit(0);
}