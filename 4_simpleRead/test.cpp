#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
using namespace std;

int main (){
    const char *dev           = "/dev/readMod";
    char output[256];
    int bytesRead;

    int fd = open(dev, O_RDONLY);
    bytesRead = read(fd, output, 256-1);
    output[bytesRead] = '\0';
    cout << output << endl;
    close(fd);

}