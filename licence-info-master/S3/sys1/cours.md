Sys 1, Carole Bernon

11/9/19

1945 eniac  100 add/s
	programme sur carte perforé
-56 1er disqur dur
-57 Fortran
-69 unix
-71 apparition du c --73 unix réécrit en c
-93 linux (open source version of unix)

processus = prog en cours d'exec

transfert depuis la mém pricipale vers mém sec = swap


____________________
service du noyau   |
	__________ |       	(vers SE)
se	|Matériel| |		utilisateur -- interpreteur de commande(shell)
	__________ |		vers (int  gr)       {communique vers le SE}
___________________|

				interface grap(vers SE)



appels système 
table des processus |tables des (fichiers système?)

______encap below
commandes(ls..) |shells (bash, sh..) |xwindow(xterm) |
utilitaire(ide, text ed, compilo..)  |biblis standard(stdio: I/o stdio.h


Unix : standart lib can be replaced with sys calls (fopen = open)

sys calls = services fournis (~64) par le noyau
Noyau: SE: gère les ressources
		Physiques: UC, mém..
		Logiques: (processus, fichiers, periph)
Matériel: services de base fournis au SE, mode utilisateur/noyau(mode privilégie)
 
CPU = unité centrale

prompt = invite de commande

$ls:
-rwx___:
l = link
b = block
c = character
p = pipe
d = directory

____
/etc : cmd et données d'administration
/dev : (devices) périphériques
___

cd : 

