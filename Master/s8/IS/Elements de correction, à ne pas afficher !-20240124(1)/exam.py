############################################################################################
#     Introduction au traitement du signal, aux signaux sonores et aux images --> EXAMEN   #
############################################################################################


import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import convolve2d


    # Transformation d'une image fréquentielle
# Version 0 : carré noir au centre
# Version 1 : bordures noires
def transform_freq(img_f, proportion, version):
    if version:
        proportion = 1 - proportion

    taille = np.shape(img_f)

    # Gestion des bords du rectangle
    debut_h = int(np.floor(taille[0]/2 - np.sqrt(proportion)*taille[0]/2))
    fin_h = int(np.floor(taille[0]/2 + np.sqrt(proportion)*taille[0]/2))
    debut_l = int(np.floor(taille[1]/2 - np.sqrt(proportion)*taille[1]/2))
    fin_l = int(np.floor(taille[1]/2 + np.sqrt(proportion)*taille[1]/2))

    # Initialisation
    if version:
        img_f_res = np.zeros(taille, dtype=complex)
    else:
        img_f_res = np.copy(img_f)

    # Calcul
    if version:
        img_f_res[debut_h:fin_h, debut_l:fin_l] = img_f[debut_h:fin_h, debut_l:fin_l]
    else:
        img_f_res[debut_h:fin_h, debut_l:fin_l] = 0

    return img_f_res



# Lecture
img = plt.imread('2cvNG.jpg')

# Affichage
plt.figure(1)
plt.imshow(img, cmap='Greys_r')
plt.title('Image Lena - Origine')
plt.draw()

# Calcul de la FFT2
img_fft2 = np.fft.fft2(img)


        # TP2_Q1. Localisation des hautes fréqences

img_f1 = transform_freq(img_fft2, 0.25, 1)

# Affichage : pensez au "+1" pour l'affichage pour éviter le log(0)
plt.figure(2)
plt.imshow(np.log(np.abs(img_f1)+1), cmap='Greys_r')
plt.title('2cv : supression des basses fréquences')
plt.draw()

# Transformation inverse
plt.figure(3)
img_new1 = np.uint8(np.abs(np.fft.ifft2(img_f1)))
plt.imshow(img_new1, cmap='Greys_r')
plt.title('Image sans basses fréquences')
plt.show()


        # TP2_Q2
# BF sont sur le bord de l'image du spectre : correction automatique dans Moodle


        # TP2_Q3. Réduction du bruit dans une image

    # Lecture et affichage de l'image "poivre et sel"

# Lecture et récupération de la taille
img_b = plt.imread('2cvBRUIT.jpg')
taille = np.shape(img_b)

# Affichage
plt.figure(4)
plt.imshow(img_b, cmap='Greys_r')
plt.title('2cv - Poivre et sel')
plt.draw()

    # Réduction du bruit avec filtrage médian

# Filtrage à la main (sans utiliser de fonction si les étudiants ont le temps...)
img_median = np.copy(img_b)

for x in range(1, taille[0]-1):
    for y in range(2, taille[1]-1):
        v = np.sort(np.ravel(img_b[x-1:x+2, y-1:y+2]))
        img_median[x-1, y-1] = v[4]

# Affichage
plt.figure(5)
plt.imshow(img_median, cmap='Greys_r')
plt.title('Image débruitée par filtre médian')
plt.show()


        # TP3_Q1. Filtre passe-haut et convolution

# Filtre passe-haut 5x5 Sharpening
fph5x5 = np.array([[-1, -1, -1, -1, -1], [-1, 0, 0, 0, -1], [-1, 0, 32, 0, -1], [-1, 0, 0, 0, -1], [-1, -1, -1, -1, -1]], float) / 16
img_fph5x5 = convolve2d(img, fph5x5, 'same')

# Affichage
plt.figure(6)
plt.imshow(img_fph5x5, cmap='gray', vmin=0, vmax=255)
plt.title('2cv - Filtre passe-haut 5x5')
plt.show()


        # TP3_Q2 - Filtrage passe-haut :
# - met en évidence les variations de luminance qui caractérisent traditionnellement les contours des objets ou la texture d'une image,
# - permet par exemple de rehausser le contraste de l'image originale.


        # TP4_Q1. Rehaussement d’une image en niveaux de gris

# Charger l’image 2cv RGB
#imgRGB = plt.imread('2cv.jpg')
#plt.imsave('2cv_float.jpg', imgRGB.astype(float)/255)
imgF = plt.imread('2cv_float.jpg')
plt.figure(7)
plt.imshow(imgF)
plt.draw()

# Masque pour Laplacien
masque_Laplacien = np.array([[0, 1, 0], [1, -4, 1], [0, 1, 0]])

# Convolution avec le masque
img_flou_Laplacien = np.zeros(imgF.shape)
img_flou_Laplacien[:,:,0] = convolve2d(imgF[:,:,0], masque_Laplacien, mode='same')
img_flou_Laplacien[:,:,1] = convolve2d(imgF[:,:,1], masque_Laplacien, mode='same')
img_flou_Laplacien[:,:,2] = convolve2d(imgF[:,:,2], masque_Laplacien, mode='same')

# Soustraire le Laplacien à l’image originale
img_flou_Laplacien_rehausee = imgF - img_flou_Laplacien
# Forcer des valeurs négatives à 0, de 0 à 255:
img_flou_Laplacien_rehausee = np.uint8(np.clip(img_flou_Laplacien_rehausee, 0, 255))

# Affichage
plt.figure(8)
plt.imshow(img_flou_Laplacien_rehausee)
plt.show()


   # TP4_Q2. Manipulation des composantes RGB (Red Green Blue)

# Chargement image
img_italie = plt.imread('drapeau_Italie.jpg')

# Affichage
plt.figure(9)
plt.imshow(img_italie)
plt.draw()
dimensions = np.shape(img_italie)

# Filtrage pour garder que le vert du drapeau Italien
seuilR = 50
masque = img_italie[:,:,0] < seuilR
img_f = np.zeros(dimensions, dtype=np.uint8)
img_f[masque, :] = img_italie[masque, :]
plt.figure(10)
plt.imshow(img_f)
plt.draw()

# Remplacer le vert de l'Italie par le bleau de la France
img_france = img_italie.copy()
img_france[masque, 0] = 0
img_france[masque, 1] = 85
img_france[masque, 2] = 164
plt.figure(11)
plt.imshow(img_france)
plt.show()