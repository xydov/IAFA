# Auxiliary functions for constructing a Huffman tree from a string


from htrees import *
from tree_func import afficher_arbre



#----------------------------------------------------------------------
# Compute character distibution from input string

#----------------------------------------------------------------------

# ex5 incremente valeur d'une clé spécifique d'un dictionnaire
def increment(dico, key): # if not in dico add clé/val au dico
    if key not in dico:
        dico[key] = 1  # add unexisting key/value
    else:
        dico[key] += 1 # increment value
    return dico

def ch_distrib(entryDico):   ### calculate the frequence distribution for a string
    dico_freq = {}
    lenghtFreqStr = float(len(entryDico))
    for c in entryDico:         # for each element in the string:
        if c not in dico_freq:  # if the element is not in the dictionnary add it with value 1
            dico_freq[c] = 1
        else:                   # if the element not in the dictionnary add 1 to the value
            dico_freq[c] += 1
    for k in dico_freq:  # divide each element with the string length
        dico_freq[k] /= lenghtFreqStr
    return dico_freq

 #print(ch_distrib(r 1("miserables"))) ############# Uncomment paragraph under 'from htrees import *' to make the readfile fonction work
#----------------------------------------------------------------------
# Construct Huffman tree from character distribution
#----------------------------------------------------------------------
def init_treeset(dict):  ## EXO 8
    treeList = []
    for k in dict:
        treeList.append(Leaf(dict[k], k))
    return treeList

def combine_two(ht1, ht2):  ## combining 2 leaves into a node
    return Node(ht1.val + ht2.val, ht1, ht2)

def combine_all_trees(treeList):  ## recursif way of combining all trees into a single one
    while len(treeList) > 1:
        treeList = sorted(treeList, key=lambda x: x.val)
        treeList[1] = combine_two(treeList[0], treeList[1])
        del treeList[0]
    return treeList[0]

def construct_huffman_tree(dict):  ## combine all functions to return the huffman tree
    return combine_all_trees(init_treeset(dict))

#----------------------------------------------------------------------
# Construct coding table corresponding to Huffman treeLeaf(0.3, 'b')
#----------------------------------------------------------------------

def dict_merge_f (d1, d2):
    dres = d1.copy()
    dres.update(d2)
    return dres


def tab_cod(m, ht):
    if isinstance(ht, Leaf):
        return {ht.code : m} #on renvoit la table correspondante à la feuille
    else:
        return dict_merge_f(tab_cod(m + [0], ht.low), tab_cod(m + [1], ht.high))


def htree_to_coding_tab(ht):
    return tab_cod([], ht) 

#----------------------------------------------------------------------
# Coding of a string with a coding table, resp. decoding with a Huffman tree
#----------------------------------------------------------------------
def code_source_string_to_bit_list(chaine, tabCod): # ex15
    lst = []
    for i in chaine:
        lst.extend(tabCod[i])
    return lst

def decode_bit_list_to_char(bl, ht, pos): # ex 17
    if isinstance(ht, Leaf):
        return ht.code, pos
    elif bl[pos] == 0:
        return decode_bit_list_to_char(bl, ht.low, pos + 1)
    return decode_bit_list_to_char(bl, ht.high, pos + 1)

def bit_list_to_string(bl): 
    chaine = []
    for i in bl:
        chaine.extend(i)
    return chaine


def decode_bit_list_to_string(bl, ht):  # ex18
    chaine = "" 
    i = 0
    while i < len(bl):
        char, i = decode_bit_list_to_char(bl, ht, i)
        chaine += char
    return chaine
