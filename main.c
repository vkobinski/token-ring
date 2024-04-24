#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {

    int descriptors[2];
    int descriptor = pipe(descriptors);

    if(descriptor != 0) {
	    perror("Could not create pipe");
	    exit(1);
    }

    char first[1000];
    first[0] = '#';

    for(int i = 1; i < 1000; i++) {
	    first[i] = '\0';
    }

    write(descriptors[1], first, 1000);

    for(int i = 0; i < 1000; i++) {
    	int child_pid = fork();

	    if(child_pid == 0) {

	    	char buf[1000];
	    	read(descriptors[0], buf, 1000);

	    	size_t size = strlen(buf);
	    	buf[size] = '0' + ((int)size);

        	write(descriptors[1], buf, 1000);
	    	exit(0);
	    }

    }

    char buf[1000];
    read(descriptors[0], buf, 1000);
    printf("%s\n", buf);

    return 0;

}
