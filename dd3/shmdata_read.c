/*************************************************************************
	> File Name: shmdata_read.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月04日 星期一 23时54分17秒
 ************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "shmdata.h"

int main() {
    int running = 1;
    void * shm = NULL;
    struct shared_use_shm *share;
    int shmid;
    shmid = shmget((key_t)1234, sizeof(struct shared_use_shm),0666|IPC_CREAT);
    if (shmid == -1) {
        fprintf(stderr, "shmget filed");
        exit(EXIT_FAILURE);
    }
    shm = shmat(shmid,0,0);
    printf("\nMemory attached at %X\n", (int)shm);
    if (shm == (void*)-1) {
        fprintf(stderr, "shmat filed");
        exit(EXIT_FAILURE);
    }
    share = (struct shared_use_shm*)shm;
    share->written = 0;
    while (running) {
        if (share->written != 0) {
            printf("you wrote %s",share->text);
            sleep(rand() % 3);
            share->written = 0;
            if (strncmp(share->text,"end",3) == 0) {
                running = 0;
            }
        }
        else {
            sleep(1);
        }
    }
    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed");
        exit(EXIT_FAILURE);
    }
    if (shmctl(shmid, IPC_RMID,0) == -1) {
        fprintf(stderr, "shmctl failed");
        exit(EXIT_FAILURE);
    }
}
