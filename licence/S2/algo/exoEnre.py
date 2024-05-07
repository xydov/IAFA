"""
class nom():
    def __init__(self, ??): #constructeur
        self.? = ??

    def __repr__(self, ??): # retourne chaine de charactere permettant de visualiser une var de ce type d'enregistrement
        return str(self.??)
class point():
    def __init__(self, x, y, visitable):
        self.x = x
        self.y = y
        self.visitable = visitable
        self.visite = False
        self.pere = None

    def __repr__(self):
        return "p(" + str(self.x) + ", " + str(self.y) + ", " + str(self.visitable) + ")"
p = point(123, 567, 1)
print(p)
"""


class Etudiant():
    def __init__(self, nom, prenom, numIne, an, notes):
        self.nom = nom
        self.prenom = prenom
        self.numIne = numIne
        self.an = an
        self.notes = np.zeros(nbNotes, float)
