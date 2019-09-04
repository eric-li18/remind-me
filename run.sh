#!/bin/bash
make > /dev/null

: '
if [ $# -lt 1 ] ; then
    echo -e "\nPlease enter 2 arguments\n"
else
fi
'
./main edit
sh ./set_crontab.sh

make clean > /dev/null