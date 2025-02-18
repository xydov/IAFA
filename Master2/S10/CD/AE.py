import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras import layers, models
from tensorflow.keras.datasets import mnist
from PIL import Image
from keras.callbacks import ModelCheckpoint
from keras.models import Model


def show (data , row , col):
    data = data.reshape(data.shape[0], 28, 28)
    count = 0
    fig , axes = plt.subplots(row,col, figsize=(16,4))
    for i in range(row):
        for j in range (col):
          axes[i,j].imshow(data[count], cmap='gray')
          count+=1

(x_train, _), (x_test, _) = mnist.load_data()


x_train = x_train.astype('float32') / 255.0
x_test = x_test.astype('float32') / 255.0


x_train = np.reshape(x_train, (x_train.shape[0], 28, 28, 1))
x_test = np.reshape(x_test, (x_test.shape[0], 28, 28, 1))

# Add random noise to the images
noise_factor = 0.5
x_train_noisy = x_train + noise_factor * np.random.normal(loc=0.0, scale=1.0, size=x_train.shape)
x_test_noisy = x_test + noise_factor * np.random.normal(loc=0.0, scale=1.0, size=x_test.shape)

# Clip the values to be between 0 and 1
x_train_noisy = np.clip(x_train_noisy, 0., 1.)
x_test_noisy = np.clip(x_test_noisy, 0., 1.)

# Plot a sample noisy image
plt.figure(figsize=(10, 4))
plt.subplot(1, 2, 1)
plt.title("Original Image")
plt.imshow(x_test[0].reshape(28, 28), cmap="gray")
plt.subplot(1, 2, 2)
plt.title("Noisy Image")
plt.imshow(x_test_noisy[0].reshape(28, 28), cmap="gray")
plt.show()

# Autoencoder Model
def build_autoencoder():
    input_img = layers.Input(shape=(28, 28, 1))
    
    # Encoder
    x = layers.Conv2D(32, (3, 3), activation='relu', padding='same')(input_img)
    x = layers.MaxPooling2D((2, 2), padding='same')(x)
    x = layers.Conv2D(64, (3, 3), activation='relu', padding='same')(x)
    x = layers.MaxPooling2D((2, 2), padding='same')(x)
    
    # Decoder
    x = layers.Conv2D(64, (3, 3), activation='relu', padding='same')(x)
    x = layers.UpSampling2D((2, 2))(x)
    x = layers.Conv2D(32, (3, 3), activation='relu', padding='same')(x)
    x = layers.UpSampling2D((2, 2))(x)
    decoded = layers.Conv2D(1, (3, 3), activation='sigmoid', padding='same')(x)
    
    autoencoder = models.Model(input_img, decoded, name='denoising_model')
    autoencoder.compile(optimizer='adam', loss='binary_crossentropy')
    return autoencoder

# Build the autoencoder
autoencoder = build_autoencoder()

# Train the autoencoder
checkpoint= ModelCheckpoint("denoising_model.keras", save_best_only=True, save_weights_only=False, verbose = 1)
trials = autoencoder.fit(x_train_noisy, x_train,
                epochs=3,
                batch_size=128,
                shuffle=True,
		callbacks= checkpoint,
                validation_data=(x_test_noisy, x_test))

decoded_imgs = autoencoder.predict(x_test_noisy)
from keras.models import load_model
autoencoder=load_model('denoising_model.keras')

n = 10
plt.figure(figsize=(20, 6))
for i in range(n):
    # Display original noisy image
    ax = plt.subplot(3, n, i + 1)
    plt.imshow(x_test_noisy[i].reshape(28, 28), cmap="gray")
    plt.title("Noisy")
    plt.axis("off")

    # Display denoised image
    ax = plt.subplot(3, n, i + n + 1)
    plt.imshow(decoded_imgs[i].reshape(28, 28), cmap="gray")
    plt.title("Denoised")
    plt.axis("off")

    # Display original clean image
    ax = plt.subplot(3, n, i + 2 * n + 1)
    plt.imshow(x_test[i].reshape(28, 28), cmap="gray")
    plt.title("Original")
    plt.axis("off")

plt.show()

import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

def denoise_image(noisy_img_path, noise_factor=0.5):
    # Charger l'image et la convertir en niveaux de gris
    noisy_img = Image.open(noisy_img_path).convert('L')
    noisy_img = noisy_img.resize((28, 28))  # Redimensionner en 28x28
    noisy_img = np.array(noisy_img) / 255.0  # Normaliser entre 0 et 1

    # Ajouter du bruit gaussien
    noisy_img = noisy_img + noise_factor * np.random.normal(loc=0.0, scale=1.0, size=noisy_img.shape)
    noisy_img = np.clip(noisy_img, 0., 1.)  # Limiter les valeurs entre 0 et 1

    # Préparer l'image pour le modèle
    noisy_img = np.reshape(noisy_img, (1, 28, 28, 1))

    # Prédire l'image débruitée
    denoised_img = autoencoder.predict(noisy_img)

    # Afficher l'image bruitée et l'image débruitée
    plt.figure(figsize=(6, 3))
    plt.subplot(1, 2, 1)
    plt.title("X")
    plt.imshow(noisy_img.reshape(28, 28), cmap="gray")
    plt.subplot(1, 2, 2)
    plt.title("Y")
    plt.imshow(denoised_img.reshape(28, 28), cmap="gray")
    plt.show()

# Utilisation de la fonction
# denoise_image("path_to_image.jpg", noise_factor=0.5)



# enleve le commentaire juste au dessous pour tester sur une image nomé '1.jpg' dans ton rép.
denoise_image('1.jpg')

show(x_test_noisy[:20], 2, 10)
pred = autoencoder.predict(x_test[:20])
pred.shape
show(pred , 2 , 10)

