# Réseau
# 11/9/19
# Rahim.KACIMI@irit.fr

compte rendu des TP avant la prochaine séance

* /!\ OSI

Téléphone Bourseul, breveté par Bell

2 familles de réseau: * Informatique * Télécommunication

à diffusion : filtrage au niveau de la machine

switch niveau 2 : par adresse mac

router  nv 3? peu effectuer le routage

# Classification
noeuds = équipement informatique
liens = fait le lien entre les noeuds
terminaux = ordinateurs...

Critères de classification:
1. Distances entre entités communicantes
	PAN (personal AN) ~1m
	LAN/RLE (Réseau local d'entreprise) ~1m à ~1km
	MAN/DAN (departemental AN)
	WAN	

2. Débit
3. Modèle d'architecture
4. Classification par AN(Private Automatic Branch eXchange, réseau tel d'un entreprise...)

# Topologie

* Point à point:
	information va d'un machine A a une machine B en traversant 1 ou pls noeuds du réseau
	noeuds est un point.

	/!\ schéma noté:
		Etoile: 1 noeuds, connexion en étoile
		Boucle:	boucle de noeuds avecc 1 connex par noeuds
		Maillé:	Maille de noeud, routage complexe mais pas de problème de canaux 'bouché'
			(Algo de routage)
* Diffusion
	Message transmit succeptible d'etre receptionné par toutes les machines du réseau	
	pas de noeuds, jonction physique directe
	Se partage un meme support
	/!\ Comment effectuer le controle et gérer les collisions
	
	Schéma:
		Anneau: boucle sans noeuds | FDDI : Par jeton
		Bus: 
		Radio/Satellite:
|_ Interconnexion de réseaux


# Normalisation:
Orga: ISO, ITU (inter telecom union)

