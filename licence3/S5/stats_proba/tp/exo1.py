import numpy as np
import numpy.random as loi
import scipy.stats as loiT
import matplotlib.pyplot as plt


# TP PROBAS et STATISTIQUES en PYTHON 2
# EXERCICE 1 : comparaison de lois uniformes : theorique & pratique


# Loi xxx # A COMPLETER...
def loi_xxx(nb_val, param1, ..., barres, pas): # A COMPLETER...

    # Loi pratique (valeurs aleatoires)
    xp = loi.xxx(param1,..., size=nb_val) # A COMPLETER...

    # Normalisation
    mini = ... # A COMPLETER...
    maxi = ... # A COMPLETER...

    # Loi theorique
    vec = np.arange(mini, maxi, pas)
    xt = loiT.xxx.xxx(vec, ) # A COMPLETER...

    # Affichage
    plt.figure()
    plt.hist(xp, barres, normed=True, label='resultat pratique')
    plt.plot(vec, xt, 'r', label='resultat theorique') # A MODIFIER dans le cas discret par 'or'
    plt.title('Loi xxx') # A COMPLETER...
    plt.xlabel('Intervalles')
    plt.ylabel('Probabilites')
    plt.legend()
    plt.show()



# DEBUT DU PROGRAMME PRINCIPAL

# Constante
nb_barres = 20
pas_reel = 0.02
pas_discret = 1

# (a) Tests de la loi Uniforme : loi discrete ou reelle au choix...
# 50 valeurs suivant une loi uniforme (min=0 & max=20)
loi_unif(50, 0, 20, nb_barres, pas_reel)
# 10000 valeurs suivant une loi uniforme (min=0 & max=20)
loi_unif(10000, 0, 20, nb_barres, pas_reel)
# 10000 valeurs suivant une loi uniforme (min=-5 & max=5)
loi_unif(10000, -5, 5, nb_barres, pas_reel)

# (b) Tests de la loi Exponentielle : loi reelle
# A COMPLETER...