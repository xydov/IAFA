#! /bin/sh

while [ $1 ]
# $# -gt 0
do
    if [ -r $1 ]
    then
        echo "$1 inaccessible"
    else
	cat $1
    fi
    shift
    # $# = expr $# - 1

done
