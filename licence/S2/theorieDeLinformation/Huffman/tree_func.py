from __future__ import print_function
import os, sys

from htrees import *
from htree_dot_noviz import display_htree


def somme(ht):
    if isinstance(ht, Leaf):
        return(ht.val)
    else:
        return(ht.val + somme(ht.low) + somme(ht.high))


def profondeur(ht):  # fonction recursive qui calcule la prodondeur d'un arbre
    if isinstance(ht, Leaf):
        return 0  # pronfondeur feuille = 0
    else:
        return (max(profondeur(ht.low), profondeur(ht.high))+1)
        # calcule max des enfants


def membre(ht, cha):  # cherche si charactère das arbre
    if isinstance(ht, Leaf):
        if ht.code == cha:
            return True
        else:
            return False
    else:
        return membre(ht.low, cha) or membre(ht.high, cha)


def afficher_arbre(ht, ind):
    if isinstance(ht, Node):
        print('  '*ind, ht.val)
        afficher_arbre(ht.low, ind + 2)
        afficher_arbre(ht.high, ind + 2)
    elif isinstance(ht, Leaf):
        print('  '*ind, ht.val, ':', ht.code)

############## EXo 4 ################


def nb_feuilles(ht):
    if isinstance(ht, Leaf):
        return 1
    else:
        return nb_feuilles(ht.low) + nb_feuilles(ht.high)


def nb_nds_int(ht):
    if isinstance(ht, Leaf):
        return 0
    else:
        return nb_nds_int(ht.low) + nb_nds_int(ht.high) + 1


def nb_noeuds(ht):
    return nb_feuilles(ht) + nb_nds_int(ht)