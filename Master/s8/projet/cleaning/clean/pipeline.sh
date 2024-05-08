#@@PAULSABIA 
#@@ script pour le nettoyage des données
# execute : ./pipeline.sh
# make sure that there are only the plane types as subdirectories in this folder.(files are allowed)

#!/bin/bash
install_library() {
    local library=$1
    if ! pip show "$library" > /dev/null; then
        echo "Installation de la bibliothèque $library..."
        pip3 install "$library"
    else
        echo -e "\t\033[32m\u2713\033[0m  $library déjà installée"
    fi
}

# Installer les bibliothèques requises
install_library pandas
install_library matplotlib
install_library numpy
install_library wordcloud
install_library sklearn

# Parcourir les répertoires
for dir in *; do
    if [ -d "$dir" ]; then
        case "$dir" in
            "A319")
                echo "Traitement du répertoire $dir..."
                cd "$dir" || continue
                for file in *; do
                    if [ -f "$file" ]; then
                        echo "Exécution du script Python de nettoyage sur le fichier : $file"
                        python ../Nettoyage_A319.py "$file"
                    fi
                done
                cd ..
                ;;
            "A321")
                echo "Traitement du répertoire $dir..."
                cd "$dir" || continue
                for file in *; do
                    if [ -f "$file" ]; then
                        echo "Exécution du script Python de nettoyage sur le fichier : $file"
                        python ../Nettoyage_A321.py "$file"
                    fi
                done
                cd ..
                ;;
            "A330")
                echo "Traitement du répertoire $dir..."
                cd "$dir" || continue
                for file in *; do
                    if [ -f "$file" ]; then
                        echo "Exécution du script Python de nettoyage sur le fichier : $file"
                        python ../Nettoyage_A330.py "$file"
                    fi
                done
                cd ..
                ;;
            "A350")
                echo "Traitement du répertoire $dir..."
                cd "$dir" || continue
                for file in *; do
                    if [ -f "$file" ]; then
                        echo "Exécution du script Python de nettoyage sur le fichier : $file"
                        python ../Nettoyage_A350.py "$file"
                    fi
                done
                cd ..
                ;;
            "Type Inconnu")
                echo "Traitement du répertoire $dir..."
                cd "$dir" || continue
                for file in *; do
                    if [ -f "$file" ]; then
                        echo "Exécution du script Python de nettoyage sur le fichier : $file"
                        python ../Nettoyage_Type_Inconnu.py "$file"
                    fi
                done
                cd ..
                ;;
            *)
                echo -e "\033[91mErreur : Le répertoire $dir est inattendu.\033[0m"
                continue
                ;;
        esac
    fi
done

