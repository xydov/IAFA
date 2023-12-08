############### PARTIE ##########################
def calcule_score_jeu(indice_jeu, liste_jeux):
  if jeu_est_un_spare(liste_jeux[0]):
    return ((liste_jeux[indice_jeu][0]+liste_jeux[indice_jeu][1]) + calcule_bonus_spare(indice_jeu, liste_jeux))
  return (liste_jeux[indice_jeu][0]+liste_jeux[indice_jeu][1])

 

def calcule_score_partie(liste_jeux_nominaux):
  total = 0
  for i in range(10):
    total += calcule_score_jeu(i, liste_jeux_nominaux)
  return total

###############  SPARE  ###############

def jeu_est_un_spare(tuple_jeux):
  if (tuple_jeux[0] != 10) and  ((tuple_jeux[0]+tuple_jeux[1]) == 10):
    return True
  else:
    return False



def calcule_bonus_spare(indice_jeu, liste_jeux):
  return liste_jeux[indice_jeu + 1][0]

############### STRIKE #################

def jeu_est_un_strike(tuple_jeu):
  if tuple_jeu[0] == 10:
    return True
  return False



def calcule_bonus_strike(indice_jeu, liste_jeux):
  if jeu_est_un_strike(liste_jeux[indice_jeu]) and jeu_est_un_strike(liste_jeux[indice_jeu+1]):
    print("STRIKE")
  return liste_jeux[indice_jeu + 1][0] + liste_jeux[indice_jeu + 1][1]