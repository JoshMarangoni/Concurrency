#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    int x = 2;
    int pid = fork();  // create new process

    if (pid == -1) {
        return 1;
    }

    if (pid == 0) {    // in child process
        x++;
    }
    sleep(2);

    printf("Process id %d. Value of x: %d\n", getpid(), x);
    if (pid != 0) {
        wait(NULL);
    }
    return 0;
}
