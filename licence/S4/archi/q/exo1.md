Kunze Tarek
21810251
# Exercice 1

## Question 1
* a)

Le nombre de bits dans une adresse représentant le n°octet à l'intérieur d'un bloc est de 3 bits : log2(8) = 3.

* b)

Le numéro d'ensemble du cache est représenté par 9 bits: log2(512) = 9

* c)
Le nombre de bit correspondant à l'étiquette est de 20 bits, ce qui correspond à l'espace restant 32-(9+3)

## Question 2
- r5 contient 0x300000, si on convertit ceci en binaire on obtient 0b0011 0000 0000 0000 0000, n° d'octet est 0 et le n° d'ensemble est 0
- r1 contiendra donc: 9A BC DE F0, puisque l'espace d'adressage est sur 32 bits
- on y ajoute 2 ce qui nous donne = F2 a la fin de la valeur (au lieu de F0)
- on ajoute 4 à l'adresse contenu dans r5, ce qui nous donne: 0100 à la fin, ce qui correspond au nombre d'octet 4, et on écrit cette valeur
- Puis on écrit la valeur de r1 à l'adresse 0x60010, ce qui donne 0b0110 0000 0000 0001 0000, donc au niveau de l'ensemble n°2, n° d'octet 0.
- Ce qui nous donne:

| n° d'ensemble | Tag     | Données |      |      |      |      |      |      |      |
| ------------: | ------- | ------: | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
|               |         |       7 | 6    | 5    | 4    | 3    | 2    | 1    | 0    |
|             0 | 0x00030 |      9A | BC   | DE   | F2   | 9A   | BC   | DE   | F0   |
|             1 | 0x00030 |      AB | CD   | 12   | 34   | 00   | 00   | 00   | 00   |
|             2 | 0x00040 |      43 | 21   | 16   | 14   | 9A   | BC   | DE   | F2   |
|             3 | 0x00052 |      19 | 39   | 19   | 45   | 19   | 67   | CD   | EF   |