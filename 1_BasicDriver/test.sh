original_dir=$(pwd)
my_dir=$(readlink -f "$0")

echo $my_dir

cd $my_dir

make clean
make

if [[ $? -eq 1]]; then 
    echo "ERROR: Failed to compile driver!"
    exit 1
fi

sudo insmod basicDriver.ko 

if [[ $? -eq 0 ]]; then
    echo "Diver was inserted successfully"
else
    echo "ERROR: Something went wrong while inserting the driver!"
    make clean
    exit 1
fi

sudo rmmod basicDriver

if [[ $? -eq 0 ]]; then
    echo "Diver was removed successfully"
else
    echo "ERROR: Something went wrong while removing the driver!"
    make clean
    exit 1
fi

echo "Test ended successfully. Cleaning"
make clean

cd $original_dir