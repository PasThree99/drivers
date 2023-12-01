#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){

    char *device = argv[1];
    int fd;
    int rc;

    fd = open(device, O_RDWR);
    if (fd < 0){
        cout << "ERROR: Open " << device << " failed" << endl;
        return 1;
    }
    
    rc = close(fd);
    if (fd < 0){
        cout << "ERROR: Close " << device << " failed" << endl;
        return 1;
    }

    return 0;
}