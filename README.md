# Fast-File-Duplication

## Environment Setting Command
sudo mkdir /tmp/ramdisk && sudo mount -t tmpfs -o size=3G tmpfs /tmp/ramdisk  
sudo swapoff -a && sudo swapon -a  
sudo sh -c "echo  3 > /proc/sys/vm/drop_caches"  
truncate -s 1G original.txt  
cp ~/Desktop/baseline /tmp/ramdisk/baseline  

## Execution Command
time ./baseline original.txt copy.txt  
diff original.txt copy.txt  
