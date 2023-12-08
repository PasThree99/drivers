#include <iostream>
#include <unistd.h>
#include <unistd.h>
using namespace std;

#define dev "/dev/driver-1"

int main(){

    int fd;

    fd = open(dev, O_RDONLY);
    char buffer[4];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    close(fd);

    for(int i = 0; i < 4; i ++){
        cout << (unsigned int) buffer[i] << endl;
    }

    return 0;
}