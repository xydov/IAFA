#!/bin/bash

ko='\e[00;31m';
wipe='\e[00m';
ok='\e[01;32m';

COMMAND="$1"
BASE=.
TESTFILES=../Test/test_files
RET=

function test_construction {
    if [ -x $BASE/$COMMAND ]
    then
    rm -f $TESTFILES/result_construct_$1.txt
#    echo "Running " $BASE/$COMMAND -c $1
	$BASE/$COMMAND -c $1 > $TESTFILES/result_construct_$1.txt
	DIFF=`diff -b -E $TESTFILES/result_construct_$1.txt $TESTFILES/references/result_construct_$1.txt`
	if [ $? -eq 0 ]
	then
		RET=0
	else
#		echo "Erreur  : " $DIFF
		RET=1
	fi
	rm -f $TESTFILES/result_construct_$1.txt
    else
	echo "Command $BASE/$COMMAND not found"
	RET=2
    fi
}

function test_search {
    if [ -x $BASE/$COMMAND ]
    then
    rm -f $TESTFILES/result_search_$1.txt
#    echo "Running " $BASE/$COMMAND -c $1
	$BASE/$COMMAND -s $1 > $TESTFILES/result_search_$1.txt 2>/dev/null
	DIFF=`diff -b -E $TESTFILES/result_search_$1.txt $TESTFILES/references/result_search_$1.txt`
	if [ $? -eq 0 ]
	then
		RET=0
	else
#		echo "Erreur  : " $DIFF
		RET=1
	fi
	rm -f $TESTFILES/result_search_$1.txt
    else
	echo "Command $BASE/$COMMAND not found"
	RET=2
    fi
}

function test_iterator {
    if [ -x $BASE/$COMMAND ]
    then
    rm -f $TESTFILES/result_iterate_$1.txt
#    echo "Running " $BASE/$COMMAND -c $1
	$BASE/$COMMAND -i $1 > $TESTFILES/result_iterator_$1.txt  2>/dev/null
	DIFF=`diff -b -E $TESTFILES/result_iterator_$1.txt $TESTFILES/references/result_iterator_$1.txt`
	if [ $? -eq 0 ]
	then
		RET=0
	else
#		echo "Erreur  : " $DIFF
		RET=1
	fi
	rm -f $TESTFILES/result_iterator_$1.txt
    else
	echo "Command $BASE/$COMMAND not found"
	RET=2
    fi
}

function test_remove {
    if [ -x $BASE/$COMMAND ]
    then
    rm -f $TESTFILES/result_remove_$1.txt
#    echo "Running " $BASE/$COMMAND -c $1
	$BASE/$COMMAND -r $1 > $TESTFILES/result_remove_$1.txt  2>/dev/null
	DIFF=`diff -b -E $TESTFILES/result_remove_$1.txt $TESTFILES/references/result_remove_$1.txt`
	if [ $? -eq 0 ]
	then
		RET=0
	else
#		echo "Erreur  : " $DIFF
		RET=1
	fi
	rm -f $TESTFILES/result_remove_$1.txt
    else
	echo "Command $BASE/$COMMAND not found"
	RET=2
    fi
}


function runtest {
 for i in $(seq 1 1 $2)
 do
	test_$1 $i
	[ $RET -eq 0 ] && printf "%-12s [${ok}OK${wipe}]\n" "$1 ($i)" 
	[ $RET -ne 0 ] && printf "%-12s [${ko}KO${wipe}]\n" "$1 ($i)" 
 done
}

echo Executing $COMMAND in directory $PWD

runtest construction 4;
runtest search 4;
runtest iterator 4;
runtest remove 4;
exit 0
