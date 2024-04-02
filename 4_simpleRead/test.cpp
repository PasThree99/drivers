#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
using namespace std;
using namespace std;

int main (int argc, char *argv[]){
    char *dev            = argv[1];
    char output[256];
    const char *expectedOutput = "This is a simple read";
    int fd;
    int rc;


    fd = open(dev, O_RDONLY);
    if (fd < 0){
        printf("ERROR: Open %s failed\n", dev);
        return 1;
    }

    rc = read(fd, output, 256 - 1);
    if (rc < 0){
        printf("ERROR: read %s failed\n", dev);
        return 1;
    }
    output[rc] = '\0';

    if(strcmp(output, expectedOutput) != 0){
        printf("ERROR: Outputs is not as expected.\n");
        printf("Got: %s\n", output);
        printf("Expected: %s\n", expectedOutput);
        return 1;
    }

    rc = close(fd);
    if (rc < 0){
        printf("ERROR: Close %s failed\n", dev);
        return 1;
    }

    return 0;
}