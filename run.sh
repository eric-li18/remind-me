make

if [ $# -lt 1 ] ; then
    echo -e "\nPlease enter 2 arguments\n"
else
    ./main $1
fi

make clean