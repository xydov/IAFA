#/usr/bin/bash

for size in 12
do
    base=`python3 n-bodies-seq.py $size 100 -nodisplay | tail -n 1`

    for target in n-bodies-par.py n-bodies-opt.py
    do
	if [ -e $target ]
	then
	    for nproc in 1 2
	    do
		val=`mpirun -n $nproc python3 $target $size 100 -nodisplay | tail -n 1`
		if [ $val != $base ]
		then
		    echo Problem with $nproc processes and $size stars
		else
		    echo OK for $nproc processes and $size stars
		fi
	    done
	else
	    echo File $target does not exist
	fi
    done
done
