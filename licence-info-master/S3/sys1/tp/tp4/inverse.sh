#! /bin/sh

if [ $# = 1 ]
then
	echo "un seul para"
	#récupère nombre de ligne
	nblignes=`wc -l \$1 | cut -f1 -d' '`
	echo $nblignes
	while [ $nblignes -gt 0 ]
	do
		nblignes=$((nblignes-1))
		echo $nblignes
	done
elif [ $# = 2 ]
then
	echo "2 para"
	cp $1 $2
	sh $0 $2
else
	echo "Erreur : inverse.sh nom_fichier [nom_fichier2]"
fi
