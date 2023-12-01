#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int main (int argc, char *argv[]){
    char *dev            = argv[1];
    char output[256];
    char *expectedOutput = "This is a simple read";
    int fd;
    int rc;

    fd = open(dev, O_RDWR);
    if (fd < 0){
        cout << "ERROR: Open " << dev << " failed" << endl;
        return 1;
    }

    rc = read(fd, output, 256 - 1);
    if (fd < 0){
        cout << "ERROR: read " << dev << " failed" << endl;
        return 1;
    }
    cout << "Output = " << output << endl;

    if(output != expectedOutput){
        cout << "ERROR: Outputs is not as expected." << endl;
        cout << "Got: " << output << endl;
        cout << "Expected: " << expectedOutput << endl;
        return 1;
    }

    rc = close(fd);
    if (fd < 0){
        cout << "ERROR: Close " << dev << " failed" << endl;
        return 1;
    }

    return 0;
}