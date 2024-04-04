#!/bin/bash

repertoire="."
parcourir() {
    local dossier="$1"
    for fichier in "$dossier"/*; do
        if [ -d "$fichier" ]; then
	echo""
	echo "Rep : 		$fichier	"
	echo""
	python sleep.py 
            parcourir "$fichier"
        elif [ -f "$fichier" ]; then
            python appliquer.py  $fichier
        fi
    done
}


if [ -d "$repertoire" ]; then
    parcourir "$repertoire"
else
    echo "erreur répertoir"
fi

