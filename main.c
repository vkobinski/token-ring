#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {

    int descriptors[2];
    int descriptor = pipe(descriptors);

    int child_pid = fork();

    pid_t my_pid = getpid();
    pid_t parent_pid = getppid();

    write(descriptors[1], "#", 1);

    char buf[20];

    read(descriptors[0], buf, 20);

    printf("%s\n", buf);

    return 0;

}
