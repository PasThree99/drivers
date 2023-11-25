device_name=/dev/persistent 

make clean
make
sudo insmod persistent.ko
major=$(cat /proc/devices | grep video4linux | awk '{print $1}')
mknod $device_name c $major 0
echo "Hello world!" > /dev/persistent
echo "Here you should see the text <Hello world!>:\n"
cat /dev/persistent
sudo rmmod persistent