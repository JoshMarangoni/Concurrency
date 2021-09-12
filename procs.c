#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    int pid = fork();  // create new process
    if (pid == -1) {
        return 1;
    }
    printf("Hello from processes\n");
    if (pid != 0) {
        wait(NULL);
    }
    return 0;
}
