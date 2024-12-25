# -*- coding: utf-8 -*-
# Modules liés à la gestion des fichiers et du système
import os


# Modules pour le traitement et l'analyse de données
import pandas as pd
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

def renommer_colonne_A319(df):
    """
    Renomme les colonnes d'un DataFrame pour correspondre aux attributs spécifiés pour les données A319.

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
        'Air / Gnd': 'Air_Gnd',
        'Computed Airspeed': 'Computed_Airspeed',
        'Mach (derived)': 'Mach',
        'Pitch Angle': 'Pitch_Angle',
        'Roll Angle': 'Roll_Angle',
        'Altitude (1013.25mB)': 'Altitude',
        'Fuel Flow Eng 1': 'Fuel_E1',
        'Fuel Flow Eng 2': 'Fuel_E2',
        'Actual Gross Weight': 'Gross_Weight',
        'Total Air Temp': 'T_Air_Temp',
        'Drift Angle': 'Drift_Angle',
        'EGT Eng 1': 'EGT_E1',
        'EGT Eng 2': 'EGT_E2',
        '_EPR Actual Eng 1': 'EPR_E1',
        '_EPR Actual Eng 2': 'EPR_E2',
        'N1 Actual Eng 1': 'N1_E1',
        'N1 Actual Eng 2': 'N1_E2',
        'N2 Actual Eng 1': 'N2_E1',
        'N2 Actual Eng 2': 'N2_E2',
        'Throttle Angle Eng 1': 'Throttle_Angle1',
        'Throttle Angle Eng 2': 'Throttle_Angle2',
        'Pack 1 Flow Ctl Valve': 'Pack_Flow_E1',
        'Pack 2 Flow Ctl Valve': 'Pack_Flow_E2',
        'Gear (left)': 'Gear_left',
        'Land Gear Squat Switch - Nose': 'L_G_S_S_N',
        'Flap Handle (derived)': 'Flap_Handle',
        'Flap Angle': 'Flap_Angle',
        'Reverser Deployed Eng 1': 'Reverser_Deployed_E1',
        'Reverser Deployed Eng 2': 'Reverser_Deployed_E2',
        'Left Spoiler 1 Out': 'Left_Spoiler_1_Out',
        'Right Spoiler 1 Out': 'Right_Spoiler_1_Out',
        'Spoiler Pos LH 2': 'Spoiler_Pos_LH_2',
        'Spoiler Pos LH 4': 'Spoiler_Pos_LH_4',
        'Spoiler Pos LH 5': 'Spoiler_Pos_LH_5',
        'Spoiler Pos RH 2': 'Spoiler_Pos_RH_2',
        'Spoiler Pos RH 3': 'Spoiler_Pos_RH_3',
        'Spoiler Pos RH 5': 'Spoiler_Pos_RH_5',
        'Speed Brake Command': 'Speed_Brake','Vitesse_Verticale': 'Vertical_Speed', 'Montée': 'Climb', 'Descente': 'Descent','Fuel':'Instant_Fuel'
    }

    # Renommer les colonnes en utilisant le dictionnaire de correspondance
    df.rename(columns=correspondance, errors='ignore', inplace=True)

    # Retourner le DataFrame avec les colonnes renommées
    return df

def traitement_gear_left_A319_A321_Type_Inconnu(df):
    """
    Fonction traitement_gear_left_A319_A321_Type_Inconnu :

    Cette fonction effectue des opérations de traitement sur la colonne 'Gear_left' d'un DataFrame,
    supprime également les taxiways, et retourne le DataFrame résultant.
    A n'appeler que sur A319 et A321 et Type_Inconnu
    Paramètres :
    - df (pd.DataFrame) : Le DataFrame sur lequel appliquer les opérations.

    Résultat :
    - df_resultat (pd.DataFrame) : Un DataFrame résultant des opérations de traitement sur la colonne 'Gear_left'.
    """

    # Traitement de la colonne 'Gear_left'
    df_dummy = pd.get_dummies(df['Gear_left'])

    columns_to_rename_gear_left = {
        'Gear down - ground (3)': 'Gear_down_ground',
        'Gear down - air (2)': 'Gear_down_air',
        'Gear in transit (0)': 'Gear_in_transit',
        'Gear up (4)': 'Gear_up',
        '? (7)': 'Gear_7'
    }

    for old_column, new_column in columns_to_rename_gear_left.items():
        if old_column in df_dummy.columns:
            df_dummy = df_dummy.rename(columns={old_column: new_column})

    columns_to_convert_to_int_gear_left = ['Gear_down_ground', 'Gear_down_air', 'Gear_in_transit', 'Gear_up', 'Gear_7']

    for column in columns_to_convert_to_int_gear_left:
        if column in df_dummy.columns:
            df_dummy[column] = df_dummy[column].astype(int)

    df = pd.concat([df, df_dummy], axis=1)

    df = df.fillna(0)
    df = df.drop(['Air_Gnd', 'Gear_left'], axis=1)

    df['Groupe'] = (df['L_G_S_S_N'] != df['L_G_S_S_N'].shift()).cumsum()

    groupe_counts = df['Groupe'].value_counts()

    if len(groupe_counts) > 3:
        quatrieme_serie = groupe_counts.index[3]
        df.loc[df['Groupe'] == quatrieme_serie, 'L_G_S_S_N'] = 1

    df = df.drop(columns=['Groupe'])
    valeur_a_supprimer = 1

    df = df[df['L_G_S_S_N'] != valeur_a_supprimer]

    return df

def nettoyage_reecriture_A319_A321_Type_Inconnu(df):
    
    """
    Fonction nettoyage_reecriture_A319_A321_Type_Inconnu :

    Cette fonction effectue des opérations de nettoyage et de réécriture sur un DataFrame,
    sans sauvegarder les modifications, puis retourne le DataFrame modifié.

    ii. Nettoyage de la colonne 'L_G_S_S_N' en extrayant les parties numériques et conversion en type entier.
    iii. Nettoyage de la colonne 'Speed_Brake' de manière similaire.
    iv. Nettoyage et réécriture de la colonne 'Air_Gnd' en créant des colonnes factices, renommage, ajout et conversion.
    v. Remplacement des valeurs NaN par 0.

    Paramètres :
    - df (pd.DataFrame) : Le DataFrame sur lequel appliquer les opérations.

    Résultat :
    - df_modifie (pd.DataFrame) : Un DataFrame résultant des opérations de nettoyage et réécriture.
    """

    # Nettoyage/Réécriture des données
    df['L_G_S_S_N'] = df['L_G_S_S_N'].str.extract('(\d+)')
    df['L_G_S_S_N'] = df['L_G_S_S_N'].astype(float).astype('Int64')

    df['Speed_Brake'] = df['Speed_Brake'].str.extract('(\d+)')
    df['Speed_Brake'] = df['Speed_Brake'].astype(float).astype('Int64')

    df_dummy = pd.get_dummies(df['Air_Gnd'])

    columns_to_rename_air_gnd = {
        'G - Gnd (7)': 'Gnd_7',
        'G - Gnd (3)': 'Gnd_3',
        'Air (0)': 'Air',
        'G - Gnd (1)': 'Gnd_1',
        'G - Gnd (2)': 'Gnd_2'
    }

    for old_column, new_column in columns_to_rename_air_gnd.items():
        if old_column in df_dummy.columns:
            df_dummy = df_dummy.rename(columns={old_column: new_column})

    df = pd.concat([df, df_dummy], axis=1)

    columns_to_convert_to_int_air_gnd = ['Gnd_7', 'Gnd_3', 'Air', 'Gnd_1', 'Gnd_2']

    for column in columns_to_convert_to_int_air_gnd:
        if column in df_dummy.columns:
            df_dummy[column] = df_dummy[column].astype(int)
    df = df.drop(['Gnd_7', 'Gnd_3', 'Air', 'Gnd_1', 'Gnd_2'], axis=1, errors='ignore')

    df = pd.concat([df, df_dummy], axis=1)

    df = df.fillna(0)

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
colonne_U_D = ['Pitch_Angle','Spoiler_Pos_LH_2','Spoiler_Pos_LH_4','Spoiler_Pos_LH_5','Spoiler_Pos_RH_2','Spoiler_Pos_RH_3','Spoiler_Pos_RH_5','Reverser_Deployed_E1','Reverser_Deployed_E2']


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



def supprimer_colonnes_A319(df):
    """
    Supprime les colonnes spécifiées pour le type d'avion A319.

    Args:
    - df (pd.DataFrame): Le DataFrame à modifier.

    Returns:
    - pd.DataFrame: Le DataFrame modifié.
    """
    colonnes_a_supprimer_A319 = [
        'City Pair - To', 'City Pair - From', 'Flight Number', 'Date - Day', 'Date - Month', 'UTC - Hour',
        'UTC - Minute', 'UTC - Second', 'Ground Speed', 'Selected Baro Setting Capt', 'Present Pos - Latitude',
        'Present Pos - Longitude', 'Magnetic Heading', 'True Heading', 'Wind Direction True', 'Wind Speed',
        'Reverser_Deployed_E1', 'Reverser_Deployed_E2', 'Fuel_E1', 'Fuel_E2','City Pair - To', 'City Pair - From', 'Flight Number', 'Date - Day', 'Date - Month', 'UTC - Hour', 'UTC - Minute', 'UTC - Second', 'Ground Speed', 'Selected Baro Setting Capt', 'Present Pos - Latitude','Present Pos - Longitude','Magnetic Heading','True Heading', 'Wind Direction True', 'Wind Speed', 'Reverser Deployed Eng 1', 'Reverser Deployed Eng 2','Fuel_E1','Fuel_E2' ,
        'City Pair - To', 'City Pair - From', 'Flight Number', 'Date - Day', 'Date - Month', 'UTC - Hour', 'UTC - Minute', 'UTC - Second', 'Ground Speed', 'Selected Baro Setting Capt', 'Present Pos - Latitude','Present Pos - Longitude','Magnetic Heading','True Heading', 'Wind Direction True', 'Wind Speed', 'Reverser Deployed Eng 1', 'Reverser Deployed Eng 2','Fuel_E1','Fuel_E2',        'City Pair - To', 'City Pair - From', 'Flight Number', 'Date - Day', 'Date - Month', 'UTC - Hour',
        'UTC - Minute', 'UTC - Second', 'Ground Speed', 'Selected Baro Setting Capt', 'Present Pos - Latitude',
        'Present Pos - Longitude', 'Magnetic Heading', 'True Heading', 'Wind Direction True', 'Wind Speed',
        'Reverser Deployed Eng 1', 'Reverser Deployed Eng 2', 'Fuel_E1', 'Fuel_E2','0'
    ]
    return df.drop(columns=colonnes_a_supprimer_A319, inplace=False, errors='ignore')


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

def gestion_phases_A319(df):
    """
    Applique le traitement de gestion des phases sur un DataFrame contenant des données de vol de l'avion A319.

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

    # Parcourir chaque ligne et calculer la valeur de la colonne "SAT"
    for index, row in df.iterrows():
        t_air_temp = row["T_Air_Temp"]
        mach = row["Mach"]
        static_air_temp = t_air_temp * (1-((1.4-mach*mach)/2))
        df.loc[index, "Static_Temp"] = static_air_temp


    # Calcul du seuil en fonction de la durée du vol
    if max(df["Time_secs"]) < 4900:
        seuil = df['Altitude'].quantile(0.88)
    elif max(df["Time_secs"]) > 10000:
        seuil = df['Altitude'].quantile(0.51)
    else:
        seuil = df['Altitude'].quantile(0.55)

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
            end_index = i  # This should be inside the loop

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


df_A319_modif  = pd.read_csv(csv_file_path)

df_A319_modif=remplacer_etoile_par_vide(df_A319_modif)


df_A319_modif=clean_and_fill_dataframe(df_A319_modif)

df_A319_modif=renommer_colonne_A319(df_A319_modif)


df_A319_modif= nettoyer_tail_number(df_A319_modif)
df_A319_modif=nettoyage_reecriture_A319_A321_Type_Inconnu(df_A319_modif)
df_A319_modif=traitement_gear_left_A319_A321_Type_Inconnu(df_A319_modif)


for column in ['Roll_Angle']:
  df_A319_modif[column] = df_A319_modif[column].apply(extract_value_L_R)
df_A319_modif= transformer_colonnes_aeronef(df_A319_modif,'A319')
for col in colonne_U_D_A321_Type_Inconnu_A319:
  df_A319_modif[col] = df_A319_modif[col].apply(extract_value_U_D)

df_A319_modif=supprimer_colonnes_A319(df_A319_modif)

df_A319_modif = convert_columns_to_numeric(df_A319_modif, numeric_columns_A319)


df_A319_modif=gestion_phases_A319(df_A319_modif)
df_A319_modif=seasonal_decomposition_detection(df_A319_modif, 'Gross_Weight', period=365, model='additive', sensitivity=3, local_window_size=500)
df_A319_modif=fill_missing_vertical_speed(df_A319_modif)















