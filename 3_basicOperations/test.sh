original_dir=$(pwd)
my_dir=$(readlink -f "$0")
device="/dev/basicOpsDevice"


cleanTest(){
    rm -f $device
    rm -f a.out
    sudo rmmod basicOps
    make clean
}

echo $my_dir
cd $my_dir

make clean
make

if [[ $? -eq 1]]; then 
    echo "ERROR: Failed to compile driver!"
    cleanTest 
    exit 1
fi

sudo insmod basicOps.ko

if [[ $? -eq 0 ]]; then
    echo "Diver was inserted successfully"
else
    echo "ERROR: Something went wrong while inserting the driver!"
    cleanTest
    exit 1;
fi

major=$(cat /proc/devices | grep registerDriver | awk '{print $1}')
echo "Driver major = $major"

sudo mknod $device c $major 0
if [[ $? -eq 1 ]]; then
    echo "Mknod failed!"
    cleanTest
    exit 1;
fi

g++ test.cpp
if [[ $? -eq 1 ]]; then
    echo "Compilation failed: test.cpp"
    cleanTest
    exit 1;
fi

./a.out
if [[ $? -eq 1 ]]; then
    echo "Test completed succesfully: open and close work as expected!"
else
    echo "Execution failed: test.cpp"
    cleanTest
    exit 1;
fi

echo "Cleaning.."
cleanTest
