#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){

    char *device = argv[1];
    int fd;
    int rc;

    printf("INFO: Opening %s\n", device);
    fd = open(device, O_RDONLY);
    if (fd < 0){
        printf("ERROR: Open %s failed (%d)\n", device, fd);
        return 1;
    }
    
    rc = close(fd);
    if (fd < 0){
        printf("ERROR: Close %s failed\n", device);
        return 1;
    }

    return 0;
}