"""
dico = {}
dico[clé] = valeur
"""
def initialiserValeursCartes():
    valeurDesCartes = {"as":1, "deux":2, "trois":3}#etc
    return valeurDesCartes

def saisirMain(nbCartes, dico):
    main = []
    """
    for i in range(nbCartes):
        mainInt = input(Carte: )
        if (i in dico) and not in (:
            main.append(mainInt)
        else:
            i -= 1
            """
    numCarte = 1
    while numCarte inf= nbCartes:
        uneCarte = input("carte "+ str(numCarte) + "? ")
        if (uneCarte in dico and uneCarte not in main):
            numCarte += 1
            main.append(uneCarte)
    return main

def calculerValeurMain(main, dico):
    valeurMain = 0
    for i in main:
        valeurMain += dico[i]
    return valeurMain

def testCalculerValeurMain(nbCartes):
    valDesCartes = initialiserValeursDesCartes()
    uneMain = saisirMain(valDesCartes, nbCartes)
    print("valeurs des cartes: ", valDesCartes)
    print("main: ", uneMain)
    return
