# -*- coding: utf-8 -*-
# Modules liés à la gestion des fichiers et du système
import os


# Modules pour le traitement et l'analyse de données
import pandas as pd
from sklearn.metrics import *
from sklearn.cluster import KMeans
import numpy as np

# Modules pour la visualisation
import matplotlib.pyplot as plt
from wordcloud import WordCloud

# Modules pour le traitement de texte
import re

# Modules pour la génération aléatoire
import random

# Modules de base
import time
import warnings
import sys

import pandas as pd



def remplacer_etoile_par_vide(df):
    """
    Remplace l'étoile (*) par une chaîne vide dans les colonnes contenant des valeurs de type chaîne.

    Paramètres :
    - df (pd.DataFrame) : DataFrame pandas à traiter.

    Retourne :
    - df_modifie (pd.DataFrame) : DataFrame avec les remplacements appliqués.
    """
    return df.apply(lambda x: x.str.replace('*', '') if x.dtype == 'object' else x)


def clean_and_fill_dataframe(df):
    """
    Supprime les NaN dans un DataFrame et remplit les valeurs manquantes avec la méthode "bfill".
    Crée également la colonne "Fuel" en combinant les colonnes spécifiées.

    Paramètres :
    - df (pd.DataFrame) : DataFrame pandas à traiter.

    Retourne :
    - df_modifie (pd.DataFrame) : DataFrame avec les modifications appliquées.
    """
    # Noms de colonnes possibles pour le flux de carburant du moteur 1 et du moteur 2
    possible_columns = [
        "Fuel Flow Engine 1 (Combined)",
        "Fuel Flow Eng 1",
        "Fuel Flow Engine 2 (Combined)",
        "Fuel Flow Eng 2"
    ]

    # Trouver les noms de colonnes réels dans le DataFrame
    real_columns = [col for col in possible_columns if col in df.columns]

    # Suppression des NaN en remplaçant chaque NaN par la valeur précédente dans la colonne respective
    for colonne in real_columns:
        last_elem = None
        for i in range(len(df)):
            if pd.isna(df[colonne][i]):
                df.loc[i, colonne] = last_elem
            else:
                last_elem = df[colonne][i]

    # Remplissage des valeurs manquantes avec la méthode "bfill"
    df_modifie = df.fillna(method='bfill')

    # Création de la colonne "Fuel" s'il y a au moins deux colonnes de flux de carburant trouvées
    fuel_columns = [col for col in real_columns if "Fuel Flow" in col]
    if len(fuel_columns) >= 2:
        df_modifie["Fuel"] = df_modifie[fuel_columns[0]].astype(float) + df_modifie[fuel_columns[1]].astype(float)

    return df_modifie

def renommer_colonne_A350(df):
    """
    Renomme les colonnes d'un DataFrame pour correspondre aux attributs spécifiés pour les données A350.

    Args:
    - df (pd.DataFrame): Le DataFrame à renommer.

    Returns:
    - pd.DataFrame: Le DataFrame avec les colonnes renommées.
    """
    # Définition du dictionnaire de correspondance
    correspondance = {
        'Time (secs)': 'Time_secs',
        'A/C Tail Number': 'Tail_Number',
        'A/C Type': 'Type',
        'RWY Engaged': 'RWY_Engaged',
        'Mach Number': 'Mach',
        'True Airspeed': 'True_Airspeed',
        'Pitch Angle - Captain': 'Pitch_Angle',
        'Roll Angle - Captain': 'Roll_Angle',
        'Baro Corrected Altitude (Combined) - Capt': 'Altitude',
        'Fuel Flow Engine 1 (Combined)': 'Fuel_E1',
        'Fuel Flow Engine 2 (Combined)': 'Fuel_E2',
        'Center Of Gravity (FCDC)': 'Center_Of_Gravity',
        'Gross Weight from FQMS (Combined)': 'Gross_Weight',
        'Static Air Temperature ADR1': 'Static_Air_Temperature',
        'Total Air Temperature (derived)': 'T_Air_Temp',
        'Drift Angle - Captain': 'Drift_Angle',
        'EGT Selected Engine 1': 'EGT_E1',
        'EGT Selected Engine 2': 'EGT_E2',
        'N1 Actual Engine 1': 'N1_E1',
        'N1 Actual Engine 2': 'N1_E2',
        'N2 Actual Selected Engine 1': 'N2_E1',
        'N2 Actual Selected Engine 2': 'N2_E2',
        'Thrust Lever Data Recorded From FCGS Engine 1': 'Thrust_E1',
        'Thrust Lever Data Recorded From FCGS Engine 2': 'Thrust_E2',
        'PRIM Flex Temp': 'Flex_Temp',
        'Pack 1 Absolute Flow': 'Pack_Flow_E1',
        'Pack 2 Absolute Flow': 'Pack_Flow_E2',
        'Landing Gear Lever Position': 'Landing_Gear_Lever_Position',
        'NLG Gear On Ground': 'Gear_On_Ground',
        'Flap Lever position': 'Flap_Handle',
        'Flap Inboard Surface Position': 'Flap_Angle',
        'Thrust Reverser Fully Deployed Engine 1': 'Left_Spoiler_1',
        'Thrust Reverser Fully Deployed Engine 2': 'Right_Spoiler_1',
        'Speed Brake Lever Position': 'Speed_Brake',
        'Left Spoiler 1 Position': 'Left_Spoiler_1',
        'Left Spoiler 2 Position': 'Left_Spoiler_2',
        'Left Spoiler 3 Position': 'Left_Spoiler_3',
        'Left Spoiler 4 Position': 'Left_Spoiler_4',
        'Left Spoiler 5 Position': 'Left_Spoiler_5',
        'Left Spoiler 6 Position': 'Left_Spoiler_6',
        'Left Spoiler 7 Position': 'Left_Spoiler_7',
        'Right Spoiler 1 Position': 'Right_Spoiler_1',
        'Right Spoiler 2 Position': 'Right_Spoiler_2',
        'Right Spoiler 3 Position': 'Right_Spoiler_3',
        'Right Spoiler 4 Position': 'Right_Spoiler_4',
        'Right Spoiler 5 Position': 'Right_Spoiler_5',
        'Right Spoiler 6 Position': 'Right_Spoiler_6',
        'Right Spoiler 7 Position': 'Right_Spoiler_7',
        'Fuel': 'Fuel',
        'Vitesse_Verticale': 'Vertical_Speed', 'Montée': 'Climb', 'Descente': 'Descent','Fuel':'Instant_Fuel'
    }

    # Renommer les colonnes en utilisant le dictionnaire de correspondance
    df.rename(columns=correspondance, errors='ignore', inplace=True)

    # Retourner le DataFrame avec les colonnes renommées
    return df


def nettoyage_reecriture_A350(df):
    """
    Fonction nettoyage_reecriture_A350 :

    Cette fonction effectue des opérations de nettoyage et de réécriture sur un DataFrame,
    sans sauvegarder les modifications, puis retourne le DataFrame modifié.

    ii. Nettoyage de la colonne 'Landing_Gear_Lever_Position' en extrayant les parties numériques et conversion en type entier.
    iii. Nettoyage de la colonne 'Gear_On_Ground' de manière similaire.
    iv. Utilisation de cumsum pour créer des groupes pour chaque série de '1' et '0'.
    v. Suppression des lignes où la valeur dans la colonne 'Landing_Gear_Lever_Position' est égale à 0.
    A n'appeler que sur A350
    Paramètres :
    - df (pd.DataFrame) : Le DataFrame sur lequel appliquer les opérations.

    Résultat :
    - df_modifie (pd.DataFrame) : Un DataFrame résultant des opérations de nettoyage et réécriture.
    """

    # Nettoyage/Réécriture des données
    df['Landing_Gear_Lever_Position'] = df['Landing_Gear_Lever_Position'].str.extract('(\d+)')
    df['Gear_On_Ground'] = df['Gear_On_Ground'].str.extract('(\d+)')

    # Convertir les colonnes en type int
    df['Landing_Gear_Lever_Position'] = df['Landing_Gear_Lever_Position'].astype('Int64')
    df['Gear_On_Ground'] = df['Gear_On_Ground'].astype('Int64')

    # Utilisation de cumsum pour créer des groupes pour chaque série de '1' et '0'
    df['Groupe'] = (df['Landing_Gear_Lever_Position'] != df['Landing_Gear_Lever_Position'].shift()).cumsum()

    # Obtenir les valeurs comptées du groupe
    groupe_counts = df['Groupe'].value_counts()

    # Vérifier si l'index [3] existe
    if len(groupe_counts) > 3:
        quatrieme_serie = groupe_counts.index[3]
        df.loc[df['Groupe'] == quatrieme_serie, 'L_G_Landing_Gear_Lever_PositionS_S_N'] = 1

    # Suppression de la colonne temporaire 'Groupe' si nécessaire
    df = df.drop(columns=['Groupe'])

    valeur_a_supprimer = 0

    # Suppression des lignes où la valeur dans la colonne 'Landing_Gear_Lever_Position' est égale à 0
    df = df[df['Landing_Gear_Lever_Position'] != valeur_a_supprimer]

    return df

def clean_A350_taxiways(df):
    """
    Fonction pour supprimer les taxiways spécifiques pour l'A350 dans un DataFrame donné.

    Paramètres :
    - df (pd.DataFrame) : Le DataFrame contenant les données de l'A350.

    Cette fonction utilise cumsum pour créer des groupes pour chaque série de '1' et '0',
    supprime les lignes où la valeur dans la colonne 'Landing_Gear_Lever_Position' est égale à 0,
    et effectue d'autres modifications spécifiques à l'A350.

    Retourne :
    - df_modifie (pd.DataFrame) : Un DataFrame résultant des modifications.
    """
    # Utilisation de cumsum pour créer des groupes pour chaque série de '1' et '0'
    df['Groupe'] = (df['Landing_Gear_Lever_Position'] != df['Landing_Gear_Lever_Position'].shift()).cumsum()

    # Obtenir les valeurs comptées du groupe
    groupe_counts = df['Groupe'].value_counts()

    # Vérifier si l'index [3] existe
    if len(groupe_counts) > 3:
        quatrieme_serie = groupe_counts.index[3]
        df.loc[df['Groupe'] == quatrieme_serie, 'L_G_Landing_Gear_Lever_PositionS_S_N'] = 1

    # Suppression de la colonne temporaire 'Groupe' si nécessaire
    df = df.drop(columns=['Groupe'])
    valeur_a_supprimer = 0

    # Suppression des lignes où la valeur dans la colonne 'Landing_Gear_Lever_Position' est égale à 0
    df = df[df['Landing_Gear_Lever_Position'] != valeur_a_supprimer]

    return df


def extract_value_U_D(value):
    """
    Fonction extract_value_U_D :

    Cette fonction prend en entrée une chaîne de caractères représentant une valeur,
    et retourne la valeur avec un signe '-' devant le nombre si le préfixe est 'D' (Down).

    Paramètres :
    - value (str) : La valeur à traiter.

    Résultat :
    - str : La valeur traitée.
    """
    # Vérifier si la valeur est une chaîne de caractères
    if isinstance(value, str):
        # Diviser la chaîne en deux parties en utilisant l'espace comme séparateur
        parts = value.strip().split(' ')
        # Vérifier si la chaîne a exactement deux parties
        if len(parts) == 2:
            # Extraire le préfixe et le nombre
            prefix, number = parts
            # Vérifier si le préfixe est 'D' (Down)
            if prefix == 'D':
                # Retourner le nombre avec un signe '-' devant
                return '-' + number
            else :
                return number
    # Si les conditions ci-dessus ne sont pas remplies, retourner la valeur d'origine
    return value


def extract_value_L_R(value):
    """
    Fonction extract_value_L_R :

    Cette fonction prend en entrée une chaîne de caractères représentant une valeur,
    et retourne la valeur avec un signe '-' devant le nombre si le préfixe est 'L' (Left).

    Paramètres :
    - value (str) : La valeur à traiter.

    Résultat :
    - str : La valeur traitée.
    """
    # Vérifier si la valeur est une chaîne de caractères
    if isinstance(value, str):
        # Diviser la chaîne en deux parties en utilisant l'espace comme séparateur
        parts = value.strip().split(' ')
        # Vérifier si la chaîne a exactement deux parties
        if len(parts) == 2:
            # Extraire le préfixe et le nombre
            prefix, number = parts
            # Vérifier si le préfixe est 'L' (Left)
            if prefix == 'L':
                # Retourner le nombre avec un signe '-' devant
                return '-' + number
    # Si les conditions ci-dessus ne sont pas remplies, retourner la valeur d'origine
    return value


#Colonnes sur lesquelles appliquer la fonction vue plus haut.
colonne_U_D_A321_Type_Inconnu_A319 = ['Pitch_Angle','Spoiler_Pos_LH_2','Spoiler_Pos_LH_4','Spoiler_Pos_LH_5','Spoiler_Pos_RH_2','Spoiler_Pos_RH_3','Spoiler_Pos_RH_5','Reverser_Deployed_E1','Reverser_Deployed_E2']
colonne_U_D_A330 = ['Pitch_Angle','Left_Spoiler_3' ,'Right_Spoiler_3','Eng1_THR_REV_fully_deployed','Eng2_THR_REV_fully_deployed']
colonne_U_D_A350 = ['Pitch_Angle','Left_Spoiler_1', 'Left_Spoiler_2', 'Left_Spoiler_3', 'Left_Spoiler_4', 'Left_Spoiler_5', 'Left_Spoiler_6', 'Left_Spoiler_7', 'Right_Spoiler_1', 'Right_Spoiler_2', 'Right_Spoiler_3', 'Right_Spoiler_4', 'Right_Spoiler_5', 'Right_Spoiler_6', 'Right_Spoiler_7']
colonne_U_D = colonne_U_D_A321_Type_Inconnu_A319


def nettoyer_tail_number(df):
    """
    Fonction nettoyer_tail_number :

    Cette fonction prend en entrée un DataFrame, nettoie la colonne 'Tail_Number' en remplaçant son contenu par
    l'élément qui commence par '.OH', puis retourne le DataFrame modifié.

    Paramètres :
    - df (DataFrame) : Le DataFrame à nettoyer.

    Résultat :
    - df (DataFrame) : Le DataFrame modifié.
    """

    # Trouver l'élément qui commence par '.OH' dans la colonne 'Tail_Number'
    element_OH = df['Tail_Number'].str.extract(r'(^\.OH.*)', expand=False).dropna().iloc[0]

    # Remplacer toute la colonne 'Tail_Number' par l'élément trouvé
    df['Tail_Number'] = element_OH

    return df




def transformer_colonnes_aeronef(df, sous_dossier):
    """
    Transforme et renomme les colonnes spécifiées pour chaque type d'aéronef rn fonction du sous dossier en fonction d'une norme mise
    en commun par l'équipe

    Parameters:
    - df (pd.DataFrame): Le DataFrame contenant les données à transformer.
    - sous_dossier (str): Le nom du sous-dossier correspondant au type d'aéronef.

    Returns:
    - pd.DataFrame: Le DataFrame transformé.

    Role de la fonction:
    - Identifie les colonnes à transformer en fonction du type d'aéronef.
    - Pour chaque colonne à transformer, extrait les valeurs numériques, les convertit en type numérique, et affiche les résultats.
    - Renomme certaines colonnes spécifiques pour le type d'aéronef A330.
    - Retourne le DataFrame transformé.
    """

    # Colonnes à transformer pour chaque type d'aéronef
    columns_to_transform_A319_A321_inconnu = ['Pack_Flow_E1', 'Pack_Flow_E2', 'Left_Spoiler_1_Out', 'Right_Spoiler_1_Out']
    columns_to_transform_A330 = ['Pack_Cont_1', 'Pack_Cont_2']
    columns_to_transform_A350 = ['RWY_Engaged', 'Thrust_E1', 'Thrust_E2','Landing_Gear_Lever_Position', 'Gear_On_Ground']


    # Identifier les colonnes à transformer en fonction du type d'aéronef
    if sous_dossier in ('A319', 'A321', 'Type_Inconnu'):
        colonne_a_tranformer = columns_to_transform_A319_A321_inconnu
    elif sous_dossier == 'A330':
        colonne_a_tranformer = columns_to_transform_A330
    elif sous_dossier == 'A350':
        colonne_a_tranformer = columns_to_transform_A350

    # Boucle pour transformer chaque colonne spécifiée
    for colonne_a_tranformer_temp in colonne_a_tranformer:
        if colonne_a_tranformer_temp in df.columns and df[colonne_a_tranformer_temp].dtype == 'O':
            # Extraire les valeurs numériques
            df[colonne_a_tranformer_temp] = df[colonne_a_tranformer_temp].str.extract('\((\d+)\)')

            # Convertir en type numérique
            df[colonne_a_tranformer_temp] = df[colonne_a_tranformer_temp].astype(float).astype('Int64')

    return df

def supprimer_colonnes_A350(df):
    """
    Supprime les colonnes spécifiées pour le type d'avion A350.

    Args:
    - df (pd.DataFrame): Le DataFrame à modifier.

    Returns:
    - pd.DataFrame: Le DataFrame modifié.
    """
    colonnes_a_supprimer_A350 = [
        'Mach Target FCU',
        'Baro Corrected Altitude (Combined) - Capt',
        'Baro Correction mb Captain - Capt. Side ADIRU',
        'A/C Present Position Latitude - Captain (Combined)',
        'A/C Present Position Longitude - Capt (Combined)',
        'Magnetic Heading Captain',
        'True Heading',
        'Wind Direction - Captain',
        'Wind Speed - Captain',
        'Thrust Reverser Fully Deployed Engine 1',
        'Thrust Reverser Fully Deployed Engine 2',
        'City Pair To', 'City Pair From', 'Flight Number (Combined)', 'Date - Day', 'Date - Month', 'Date - Year',
        'UTC Hours', 'UTC Minutes', 'UTC Seconds', 'Any Gear on Ground', 'Ground Speed',
        'Indicated Air Speed - Captain', 'Mach_Target_FCU', 'Baro_Corrected_Altitude_Combined_Capt',
        'Baro_Correction_mb_Captain_Capt_Side_ADIRU', 'Present_Position_LatitudeCaptain(Combined)',
        'Present_Position_Longitude_Capt(Combined)', 'Magnetic_Heading_Captain', 'True_Heading',
        'Wind_Direction_Captain', 'Wind Speed_Captain', 'Thrust_Reverser_Fully_Deployed_E1',
        'Thrust_Reverser_Fully_Deployed_E2', 'Fuel_E1', 'Fuel_E2'
    ]
    return df.drop(columns=colonnes_a_supprimer_A350, inplace=False, errors='ignore')


from statsmodels.tsa.seasonal import seasonal_decompose

def seasonal_decomposition_detection(df, column, period=365, model='additive', sensitivity=3, local_window_size=500):
    """
    Détecte et corrige les anomalies saisonnières dans une série temporelle en utilisant la décomposition saisonnière.

    Args:
    - df (DataFrame): Le DataFrame d'entrée contenant les données de la série temporelle.
    - column (str): Le nom de la colonne contenant les données de la série temporelle.
    - period (int): La période de la composante saisonnière. Par défaut, 365.
    - model (str): Le type de modèle de décomposition saisonnière à utiliser. Par défaut, 'additive'.
    - sensitivity (int): Le seuil de sensibilité pour détecter les anomalies. Par défaut, 3.
    - local_window_size (int): La taille de la fenêtre locale pour calculer les valeurs corrigées autour des anomalies. Par défaut, 500.

    Returns:
    - df (DataFrame): Le DataFrame avec les anomalies saisonnières détectées et corrigées.
    """
    # Ensure the column has no NaN values
    df[column].fillna(method='ffill', inplace=True)

    # Décompose la série temporelle en composantes de tendance, saisonnières et résiduelles
    decomposition = seasonal_decompose(df[column], model=model, period=period)

    # Calcule les résidus et remplit les valeurs manquantes au début/à la fin
    df['residual'] = decomposition.resid
    df['residual'].fillna(method='bfill', inplace=True)

    # Calcule l'écart-type des résidus
    residual_std = df['residual'].std()

    # Détecte les anomalies en fonction du seuil de sensibilité
    df['anomaly'] = (abs(df['residual']) > (sensitivity * residual_std)).astype(int)

    # Corrige les valeurs anormales en les remplaçant par la moyenne des valeurs dans une fenêtre locale
    df['corrected_values'] = df.apply(lambda x: x[column] if x['anomaly'] == 0 else df[x.name - local_window_size//2:x.name + local_window_size//2 + 1][column].mean(), axis=1)

    # Remplace les valeurs originales de la colonne par les valeurs corrigées
    df[column] = df['corrected_values']

    # Supprime les colonnes inutiles
    df.drop(['residual', 'anomaly', 'corrected_values'], axis=1, inplace=True)

    return df


import pandas as pd

def fill_missing_vertical_speed(df):
    """
    Fill missing vertical speed values in a DataFrame using an imputation method.

    Args:
    - df (DataFrame): The DataFrame containing altitude and time data.

    Returns:
    - df (DataFrame): The DataFrame with filled missing vertical speed values.
    """

    # Create a boolean mask to keep non-missing altitude values
    mask_keep = ~df['Altitude'].isnull()

    # Calculate vertical speed using differences between altitudes and times
    df['Vitesse_Verticale'] = df['Altitude'].diff() / df['Time_secs'].diff()

    # Replace NaN in the first row with zero
    df.loc[df.index[0], 'Vitesse_Verticale'] = 0

    # Forward-fill missing vertical speed values
    df['Vitesse_Verticale'].fillna(method='ffill', inplace=True)

    # Set vertical speed to NaN for rows with missing altitude values
    df.loc[~mask_keep, 'Vitesse_Verticale'] = None

    return df


def seasonal_decomposition_detection_and_correction(df, column, period=200, model='additive', sensitivity=3):
    """
    Détection et correction des anomalies saisonnières dans une série chronologique à appliquer pour l'A319, A321, A330, Type Inconnu

    Args:
    - df (DataFrame): Le DataFrame contenant la série chronologique.
    - column (str): Le nom de la colonne contenant la série chronologique.
    - period (int): La période de la composante saisonnière. Par défaut, 200.
    - model (str): Le modèle de décomposition saisonnière à utiliser. Par défaut, 'additive'.
    - sensitivity (int): La sensibilité pour détecter les anomalies saisonnières. Par défaut, 3.

    Returns:
    - df (DataFrame): Le DataFrame avec les anomalies saisonnières détectées et corrigées.
    """

    # Décomposition saisonnière
    decomposition = seasonal_decompose(df[column], model=model, period=period, extrapolate_trend='freq')
    df['trend'] = decomposition.trend
    df['seasonal'] = decomposition.seasonal
    df['residual'] = decomposition.resid

    # Gestion des valeurs manquantes dans les résidus
    df['residual'].fillna(method='bfill', inplace=True)

    # Calcul de l'écart-type des résidus
    residual_std = df['residual'].std()

    # Identification des anomalies
    df['anomaly'] = (abs(df['residual']) > (sensitivity * residual_std)).astype(int)

    # Correction des anomalies en utilisant l'interpolation linéaire
    df[column] = df[column].copy()
    df.loc[df['anomaly'] == 1, column] = np.nan  # Remplacez les anomalies par NaN
    df[column].interpolate(method='linear', inplace=True)  # Interpolation linéaire
    return df


def gestion_phases_A350(df):
    """
    Applique le traitement de gestion des phases sur un DataFrame contenant des données de vol de l'avion A350.

    Args:
        df (DataFrame): Le DataFrame contenant les données de vol.

    Returns:
        DataFrame: Le DataFrame modifié avec les colonnes 'Cruise', 'Montée' et 'Descente'.
    """
    # Convert columns to appropriate data types
    df['T_Air_Temp'] = pd.to_numeric(df['T_Air_Temp'], errors='coerce')
    df['Mach'] = pd.to_numeric(df['Mach'], errors='coerce')

    # Check for non-numeric values in the columns
    print(df.dtypes)

    # Convert columns to appropriate data types
    df['T_Air_Temp'] = df['T_Air_Temp'].astype(float)
    df['Mach'] = df['Mach'].astype(float)
    # Calcul du seuil en fonction de la durée du vol
    if max(df["Time_secs"]) > 50000:
        seuil = df['Altitude'].quantile(0.24)
    elif max(df["Time_secs"]) > 40000:
        seuil = df['Altitude'].quantile(0.34)
    elif max(df["Time_secs"]) > 35000 :
        seuil = df['Altitude'].quantile(0.25)
    elif 30000 < max(df["Time_secs"]) < 40000:
        seuil = df['Altitude'].quantile(0.35)
    elif max(df["Time_secs"]) < 30000:
        seuil = df['Altitude'].quantile(0.54)

    # Suppression des colonnes existantes si elles existent déjà
    df = df.drop("Cruise", axis=1, errors='ignore')
    df = df.drop("Montée", axis=1, errors='ignore')
    df = df.drop("Descente", axis=1, errors='ignore')

    # Création de la colonne 'Cruise' basée sur le seuil
    df['Cruise'] = df['Altitude'].map(lambda x:  x > seuil)

    # Recherche des indices de début et fin de blocs 'Cruise' (True)
    boolean_list = df['Cruise'].tolist()
    start_index = None
    end_index = None
    for i, value in enumerate(boolean_list):
        if value:
            if start_index is None:
                start_index = i
            end_index = i

    # Mise à True des valeurs à l'intérieur du bloc 'Cruise'
    if start_index is not None and end_index is not None:
        for i in range(start_index + 1, end_index):
            if not boolean_list[i]:
                boolean_list[i] = True

    df['Cruise'] = boolean_list

    # Conversion de la colonne 'Cruise' en entiers (0 ou 1)
    df['Cruise'] = df['Cruise'].astype(int)

    # Recherche des indices du début et de la fin de la phase 'Montée' (max)
    indice_premier_1 = df['Cruise'].idxmax()
    indice_dernier_1 = df['Cruise'][::-1].idxmax()

    # Création des colonnes 'Montée' et 'Descente'
    df['Montée'] = np.where(df.index <= indice_premier_1-1, 1, 0)
    df['Descente'] = np.where(df.index > indice_dernier_1, 1, 0 )
    df['Static_Temp'] = None
    # Parcourir chaque ligne et calculer la valeur de la colonne "SAT"
    for index, row in df.iterrows():
        t_air_temp = row["T_Air_Temp"]
        mach = row["Mach"]
        static_air_temp = t_air_temp * (1-((1.4-mach*mach)/2))
        df.loc[index, "Static_Temp"] = static_air_temp

    return df



def convert_columns_to_numeric(df, columns):
    """
    Convert specified columns in a DataFrame to numeric types.

    Parameters:
    - df (DataFrame): The DataFrame containing the columns to be converted.
    - columns (list): A list of column names to be converted to numeric types.

    Returns:
    - DataFrame: The DataFrame with specified columns converted to numeric types.
    """
    columns_present = [col for col in columns if col in df.columns]

    # Convert columns to numeric
    df[columns_present] = df[columns_present].apply(pd.to_numeric, errors='coerce')

    return df

numeric_columns_A319 = ['Pitch_Angle', 'Roll_Angle', 'Altitude', 'Gross_Weight', 'Drift_Angle', 'EGT_E1', 'EGT_E2', 'EPR_E1', 'EPR_E2',
                   'N1_E1', 'N1_E2', 'N2_E1', 'N2_E2', 'Throttle_Angle1', 'Throttle_Angle2', 'Flap_Angle', 'Spoiler_Pos_LH_2',
                   'Spoiler_Pos_LH_4', 'Spoiler_Pos_LH_5', 'Spoiler_Pos_RH_2', 'Spoiler_Pos_RH_3', 'Spoiler_Pos_RH_5','Static_Temp','Reverser_Deployed_E1','Reverser_Deployed_E2' ]

numeric_columns_A330 = [
    'Computed_Airspeed',
    'Mach',
    'Pitch_Angle',
    'Roll_Angle',
    'Altitude',
    'Total_Fuel',
    'Center_Of_Gravity',
    'Gross_Weight',
    'Static_Air_Temperature',
    'Drift_Angle',
    'EGT_E1',
    'EGT_E2',
    'N1_E1',
    'N1_E2',
    'N2_E1',
    'N2_E2',
    'Throttle_Angle_E1',
    'Throttle_Angle_E2',
    'Flex_Temp',
    'APU_Fuel_flow',
    'Flap_Handle',
    'Flap_Angle',
    'Speed_Brake','Reverser_Deployed_E1','Reverser_Deployed_E2'
]

numeric_columns_A350 = [
    "Tail_Number",
    "Type",
    "City Pair To",
    "City Pair From",
    "Flight Number (Combined)",
    "RWY_Engaged",
    "Date - Day",
    "Date - Month",
    "Date - Year",
    "UTC Hours",
    "UTC Minutes",
    "UTC Seconds",
    "Any Gear on Ground",
    "Ground Speed",
    "Indicated Air Speed - Captain",
    "Mach",
    "Mach Target FCU",
    "True_Airspeed",
    "Pitch_Angle",
    "Roll_Angle",
    "Altitude",
    "Standard Pressure Altitude (Combined) - Capt.",
    "Baro Correction mb Captain - Capt. Side ADIRU",
    "A/C Present Position Latitude - Captain (Combined)",
    "A/C Present Position Longitude - Capt (Combined)",
    "Magnetic Heading Captain",
    "True Heading",
    "Fuel_E1",
    "Fuel_E2",
    "Center_Of_Gravity",
    "Gross_Weight",
    "Static_Air_Temperature",
    "T_Air_Temp",
    "Drift_Angle",
    "Wind Direction - Captain",
    "Wind Speed - Captain",
    "EGT_E1",
    "EGT_E2",
    "N1_E1",
    "N1_E2",
    "N2_E1",
    "N2_E2",
    "Thrust_E1",
    "Thrust_E2",
    "Flex_Temp",
    "Pack_Flow_E1",
    "Pack_Flow_E2",
    "Landing_Gear_Lever_Position",
    "Gear_On_Ground",
    "Flap_Handle",
    "Flap_Angle",
    "Speed_Brake",
    "Left_Spoiler_2",
    "Left_Spoiler_3",
    "Left_Spoiler_4",
    "Left_Spoiler_5",
    "Left_Spoiler_6",
    "Left_Spoiler_7",
    "Right_Spoiler_2",
    "Right_Spoiler_3",
    "Right_Spoiler_4",
    "Right_Spoiler_5",
    "Right_Spoiler_6",
    "Right_Spoiler_7"
]


if len(sys.argv) < 2:
    print("Usage: python script.py <path_to_csv_file>")
    sys.exit(1)
csv_file_path = sys.argv[1]


df_A350_modif  = pd.read_csv(csv_file_path)



df_A350_modif=remplacer_etoile_par_vide(df_A350_modif)
df_A350_modif=clean_and_fill_dataframe(df_A350_modif)

df_A350_modif=renommer_colonne_A350(df_A350_modif)



df_A350_modif= nettoyer_tail_number(df_A350_modif)
df_A350_modif=nettoyage_reecriture_A350(df_A350_modif)


for column in ['Roll_Angle']:
  df_A350_modif[column] = df_A350_modif[column].apply(extract_value_L_R)
df_A350_modif= transformer_colonnes_aeronef(df_A350_modif,'A350')
for col in colonne_U_D_A350:
  df_A350_modif[col] = df_A350_modif[col].apply(extract_value_U_D)

df_A350_modif=supprimer_colonnes_A350(df_A350_modif)

df_A350_modif = convert_columns_to_numeric(df_A350_modif, numeric_columns_A350)
print(df_A350_modif.info())

df_A350_modif = clean_A350_taxiways(df_A350_modif)
df_A350_modif=gestion_phases_A350(df_A350_modif)
df_A350_modif=seasonal_decomposition_detection_and_correction(df_A350_modif, 'Gross_Weight', period=365, model='additive', sensitivity=3, local_window_size=500)
df_A350_modif=fill_missing_vertical_speed(df_A350_modif)



