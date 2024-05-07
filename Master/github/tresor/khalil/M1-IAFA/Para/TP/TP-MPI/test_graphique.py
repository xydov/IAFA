# python3 test_graphique.py

import matplotlib.pyplot as plt

plt.plot([0, 1, 1, 0], [1, 0, 1, 0])

plt.draw()
plt.show(block=False)
# une pause de 2 secondes, juste pour voir que ça s'affiche bien
# on doit l'enlever dès que ça marche ;)
plt.pause(2)
