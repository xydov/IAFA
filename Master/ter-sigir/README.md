Ce repertoir contient la participation de Nouh et Alexandra à la conference de ReNeuIR@SIGIR2024.
pour le DockerFile , c'est l'organisateur de la conférence qui nous l'a fait à cause des problémes sur nos machines (jusqu'à maintenant j'arrive a faire le build mais pas à le lancer).
sinon les deux fichiers my_chercher.py et plaid-x.py representent globalement nos deux pipelines qu'on a déposé.
pour les lancer , il suffit de passer l'id du dataset en paramettre et attendre le lancement . sur cpu ca prend approximativement 3h pour la generation du run.txt . 

Exemple :
  
```
python3 my_chercher.py  reuneuir-2024/dl-top-10-docs-20240701-training

```

avec plaid-x : 

```
python3 plaid-x.py --dataset_id reuneuir-2024/dl-top-1000-docs-20240701-training
```
