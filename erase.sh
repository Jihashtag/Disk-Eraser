make && make clean
trap "echo skipping...\n" 2
./erase $1 $2 $3
trap "echo skipping...\n" 2
if [ $1 ]
then
	echo $1
	mkfs.msdos -I $1
	echo "n\np\n\n\n\nw\n" | fdisk $1
	a=$1"1"
	echo $a
	mkfs.fat $a
fi
echo "Done"
