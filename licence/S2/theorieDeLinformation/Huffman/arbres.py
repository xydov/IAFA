from __future__ import print_function

from htrees import *
from htree_dot_noviz import display_htree
from tree_func import *

a1 = Node(0.5, Leaf(0.2, 'a'), Leaf(0.3, 'b'))
#Ajout
a2 = Node(0.5, Leaf(0.2, 'a'), Node(0.3, Leaf(0.2, 'c'), Leaf(0.3, 'b')))
a3 = Node(0.7, Node(0.4, Leaf(0.2, 'a'), Leaf(0.2, 'b')), Leaf(0.3, 'c'))
a4 = Node(0.9, Node(0.8, Leaf(0.7, 'g') ,Leaf(0.1, 'f')), Node(0.1, Leaf(0.05, 'g') ,Leaf(0.05, 'f')))
"""
print(somme(a3))
print(profondeur(a3))
print(profondeur(a1))
print(membre(a1, 'a'))
print(membre(a2, 'b'))
print(membre(a3, 'd'))
afficher_arbre(a3, 0)

print(nb_feuilles(a1))
print(nb_feuilles(a2))
print(nb_feuilles(a3))

"""
print(nb_nds_int(a4))
print(nb_feuilles(a4))
print(nb_noeuds(a4))
