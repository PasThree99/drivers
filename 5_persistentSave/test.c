#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main (void){
    char *dev           = "/dev/persistent";
    char *input         = "Hello world!";
    char output[256];

    int fd = open(dev, O_RDWR);
    write(fd, input, strlen(input));
    read(fd, output, sizeof(output)-1);
    printf("Output = %s\nExpected = %s\n", output, input);
    close(fd);

}