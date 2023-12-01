#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){

    char *device = argv[1];
    int fd;
    char buffer[1];
    int bytes_read;
    int rc;

    fd = open(device, O_RDONLY);
    if (fd < 0){
        printf("ERROR: Open %s failed (%d)\n", device, fd);
        return 1;
    }

    bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read < 0){
        printf("ERROR: Open %s failed (%d)\n", device, fd);
        return 1;
    }

    rc = close(fd);
    if (rc < 0){
        printf("ERROR: Open %s failed (%d)\n", device, fd);
        return 1;
    }

    for(int i = 0; i < 1; i ++){
        printf("%d\n", (unsigned int) buffer[i]);;
    }

    return 0;
}