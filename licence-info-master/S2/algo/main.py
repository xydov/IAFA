from bowling import *

# Ce fichier contient les fonctions permettant de tester les fonctions que vous devez écrire dans le fichier "Bowling.py"
# Ces fonctions de tests spécifient d'une part les structures de données que vous devez utiliser mais aussi les fonctions
# que vous devez implanter. Vous ne devez pas modifier ce fichier.
#

# Fonction lançant l'ensemble des fonctions de tests implantées dans la suite du fichier
#
def run_tests():
    # 1. tests dans les cas simples
    print("DEBUT PHASE 1")
    test_calcule_score_jeu_cas_nominal()
    test_calcule_score_partie_cas_nominal()
    print("PHASE 1 : OK")

    # 2. tests prenant en compte les spares
    print("DEBUT PHASE 2")
    test_jeu_est_un_spare()
    test_calcule_bonus_spare()
    test_calcule_score_jeu_cas_spare()
    test_calcule_score_partie_cas_spares_seulement()
    print("PHASE 2 : OK")

    # 3. tests prenant en compte les strikes
    print("DEBUT PHASE 3")
    test_jeu_est_un_strike()
    test_calcule_bonus_strike_cas_nominal()
    test_calcule_bonus_strike_cas_2_strikes_consecutifs()
    test_calcule_bonus_strike_cas_1_strike_en_fin()
    test_calcule_score_jeu_cas_strike()
    test_calcule_score_partie_cas_strikes_seulement()
    print("PHASE 3 : OK")

#
#   Les fonctions de tests
#

# Un jeu est représenté par un tuple
# Les variables ci-dessous permettent de définir des exemples de jeux qui serviront dans les tests
#
strike = (10, 0)
spare_0_10 = (0, 10)
spare_5_5 = (5, 5)
jeu_nominal_6_1 = (6, 1)


# Test de la fonction "calcule_score_jeu(indice_jeu, liste_jeux)" dans un cas nominal (un cas simple)
# indice_jeu désigne l'indice du jeu dans la liste de jeux référencée par liste_jeux
#
def test_calcule_score_jeu_cas_nominal():
    indice_jeu = 0
    liste_jeux = [jeu_nominal_6_1]
    assert liste_jeux[indice_jeu][0] + liste_jeux[indice_jeu][1] == calcule_score_jeu(indice_jeu, liste_jeux), \
        "Le calcul du score d'un jeu nominal se fait en ajoutant le nombre de quilles tombées à chaque lancer"


# Test de la fonction "calcule_score_partie(liste_jeux)" dans un cas nominal (un cas simple)
# liste_jeux désigne la liste des jeux de la partie
#
def test_calcule_score_partie_cas_nominal():
    liste_jeux_nominaux = [jeu_nominal_6_1] * 10
    assert 70 == calcule_score_partie(liste_jeux_nominaux), "Score devrait valoir 70"


# Test de la fonction "jeu_est_un_spare(jeu)"
#
def test_jeu_est_un_spare():
    assert False == jeu_est_un_spare(strike), "Ce jeu n'est pas un spare !"
    assert True == jeu_est_un_spare(spare_0_10), "Ce jeu est bien un spare !"
    assert True == jeu_est_un_spare(spare_5_5), "Ce jeu est bien un spare !"
    assert False == jeu_est_un_spare(jeu_nominal_6_1), "Ce jeu n'est pas un spare !"

# Test de la fonction "calcule_bonus_spare(indice_jeu, liste_jeux)"
# indice_jeu désigne l'indice du jeu dans la liste de jeux référencée par liste_jeux
#
def test_calcule_bonus_spare():
    indice_jeu = 0
    liste_jeux = [spare_5_5, jeu_nominal_6_1]
    assert liste_jeux[indice_jeu + 1][0] == calcule_bonus_spare(indice_jeu, liste_jeux), \
        "Le bonus d'un spare obtenu au jeu courant est toujours le nombre de quilles tombées au premier lancer du jeu suivant"

# Test de la fonction "calcule_score_jeu(indice_jeu, liste_jeux)" quand le jeu est un spare
# indice_jeu désigne l'indice du jeu dans la liste de jeux référencée par liste_jeux
#
def test_calcule_score_jeu_cas_spare():
    indice_jeu = 0
    liste_jeux = [spare_5_5, jeu_nominal_6_1]
    assert 10 + calcule_bonus_spare(indice_jeu, liste_jeux) == calcule_score_jeu(indice_jeu, liste_jeux), \
        "le calcul du score d'un spare s'effectue en ajoutant le bonus calculé pour le spare au nombre de quilles tombées, c'est à dire 10"

# Test de la fonction "calcule_score_partie(liste_jeux)" dans le cas où tous les jeux sont des spares
# liste_jeux désigne la liste des 10 jeux de la partie auquel s'ajoute un jeu supplémentaire
#
def test_calcule_score_partie_cas_spares_seulement():
    liste_spares = [spare_5_5] * 10 + [(5, 0)]
    assert 150 == calcule_score_partie(liste_spares), "Score devrait valoir 150"


# Test de la fonction "jeu_est_un_strike(jeu)"
#
def test_jeu_est_un_strike():
    assert True == jeu_est_un_strike(strike), "Ce jeu est bien un strike !"
    assert False == jeu_est_un_strike(spare_0_10), "Ce jeu n'est pas un strike !"
    assert False == jeu_est_un_strike(spare_5_5), "Ce jeu n'est pas un strike !"
    assert False == jeu_est_un_strike(jeu_nominal_6_1), "Ce jeu n'est pas un strike !"

# Test de la fonction "calcule_bonus_strike(indice_jeu, liste_jeux)" dans un cas nominal (un cas simple)
# indice_jeu désigne l'indice du jeu dans la liste de jeux référencée par liste_jeux
#
def test_calcule_bonus_strike_cas_nominal():
    indice_jeu = 0
    liste_jeux = [strike, jeu_nominal_6_1]
    assert liste_jeux[indice_jeu + 1][0] + liste_jeux[indice_jeu + 1][1] == calcule_bonus_strike(indice_jeu, liste_jeux), \
        "Le bonus d'un strike obtenu au jeu courant est le nombre de quilles tombées au deux lancers du jeu suivant quand le jeu suivant n'est pas un strike"


# Test de la fonction "calcule_bonus_strike(indice_jeu, liste_jeux)" dans le cas de deux strikes consécutifs
# indice_jeu désigne l'indice du jeu dans la liste de jeux référencée par liste_jeux
#
def test_calcule_bonus_strike_cas_2_strikes_consecutifs():
    indice_jeu = 0
    liste_jeux = [strike, strike, jeu_nominal_6_1]
    assert 10 + liste_jeux[indice_jeu + 2][0] == calcule_bonus_strike(indice_jeu, liste_jeux), \
        "Le bonus d'un strike obtenu au jeu n est 10 + le nombre de quilles tombées au premier lancer du jeu n+2 quand le jeu n+1 est un strike"


# Test de la fonction "calcule_bonus_strike(indice_jeu, liste_jeux)" dans le cas d'un strike obtenu au dernier jeu
# indice_jeu désigne l'indice du jeu dans la liste de jeux référencée par liste_jeux
#
def test_calcule_bonus_strike_cas_1_strike_en_fin():
    indice_jeu = 9
    liste_jeux = [jeu_nominal_6_1] * 9 + [strike] + [(10, 10)]
    assert liste_jeux[indice_jeu + 1][0] + liste_jeux[indice_jeu + 1][1] == calcule_bonus_strike(indice_jeu,liste_jeux), \
        "Le bonus d'un strike obtenu au dernier jeu est le nombre de quilles tombées aux deux lancers supplémentaires de fin de partie"

# Test de la fonction "calcule_score_jeu(indice_jeu, liste_jeux)" quand le jeu est un strike
# indice_jeu désigne l'indice du jeu dans la liste de jeux référencée par liste_jeux
#
def test_calcule_score_jeu_cas_strike():
    indice_jeu = 0
    liste_jeux = [strike, jeu_nominal_6_1]
    assert 10 + calcule_bonus_strike(indice_jeu, liste_jeux) == calcule_score_jeu(indice_jeu, liste_jeux), \
        "le calcul du score d'un strike s'effectue en ajoutant le bonus calculé pour le strike au nombre de quilles tombées, c'est à dire 10"

# Test de la fonction "calcule_score_partie(liste_jeux)" dans le cas où tous les jeux sont des strikes
# liste_jeux désigne la liste des jeux de la partie auquel s'ajoute un jeu supplémentaire
#
def test_calcule_score_partie_cas_strikes_seulement():
    liste_strikes = [strike] * 10 + [(10, 10)]
    assert 300 == calcule_score_partie(liste_strikes), "Score devrait valoir 300"


#
# Exécution des tests
#

run_tests()