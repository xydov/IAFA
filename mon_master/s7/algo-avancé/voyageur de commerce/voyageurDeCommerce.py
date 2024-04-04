import numpy as np
import sys 
import random
import math
import copy
import time

def lire_instance(filename):
    with open(filename, 'r') as f:
        first_line = f.read()
        tokens = first_line.split()
        n = int(tokens[0])
        XY = np.zeros((n,2))
        for i in range(n):
            for j in range(2):
                XY[i,j] = int(tokens[i * 3 + j + 2])
    return XY, n
#2.1
def init_solution(n):
    return np.random.permutation(n)

#2.2
def euclidean_distance(point1, point2):
    # Calcule la distance euclidienne entre deux points
    distance = 0
    for i in range(len(point1)):
        distance += (point1[i] - point2[i]) ** 2
    return math.sqrt(distance)

def calculer_solution(cities, X, n):
        return np.linalg.norm(cities[X[0]]) + np.linalg.norm(cities[X[-1]]) + np.linalg.norm(cities[X[1:]] - cities[X[:-1]], axis=1).sum()

#2.3
def meilleur_voisin(XY, s, n):
    val_min = math.inf
    solutions = []

    for i in range(n):
        for j in range(i+1,n):
            s_loc = np.copy(s)
            s_loc[i], s_loc[j] = s_loc[j], s_loc[i]
            val_loc = calculer_solution(XY, s_loc, n)
        
            if val_loc == val_min:
                solutions.append(s_loc)
            elif val_loc < val_min:
                solutions = [s_loc]
                val_min = val_loc
    
    indice = random.randint(0, len(solutions) - 1)
    return solutions[indice] 
#2.4
def meilleur(s_prime, s, XY, n):
    return calculer_solution(XY, s, n) > calculer_solution(XY ,s_prime ,n)

def hill_climbing_red(XY ,max_essais ,n, max_depl):
    start = time.process_time()
    result = math.inf, 0
    # On effectue plusieurs essais de hill climbing
    for i in range(max_essais):
        # solution initiale au hasard
        solution = init_solution(n)
        print(f"Essai {i+1} : solution initiale = {solution}")

        nb_depl = 0

        STOP = False
        while not STOP and nb_depl < max_depl:
            # On cherche le meilleur voisin
            voisin = meilleur_voisin(XY ,solution, n)

            if meilleur(voisin, solution, XY, n):
                solution = voisin
                nb_depl += 1
            else:
                STOP = True
                
        valeur = calculer_solution(XY,solution,n)
        if result[0] > valeur:
            result = valeur, nb_depl 
        print(f"Solution finale = {solution} valeur => {calculer_solution(XY,solution,n)} (nombre de déplacements = {nb_depl})")
    end = time.process_time()
    print(end-start)

#2.5
def in_table(s, Tabou):
    for s_t in Tabou:
        if np.all(s==s_t):
            return True
    return False

def meilleur_voisin_non_tabou(XY ,Tabou ,s ,n):
    val_min = math.inf
    solutions = []
    

    for i in range(n):
        for j in range(i+1,n):
        
            s_loc = np.copy(s)
            s_loc[i], s_loc[j] = s_loc[j], s_loc[i]
            val_loc = calculer_solution(XY, s_loc, n)
        
            if (val_loc == val_min) and (not in_table(s_loc, Tabou)):
                solutions.append(s_loc)
            elif (val_loc < val_min) and (not in_table(s_loc, Tabou)):
                solutions = [s_loc]
                val_min = val_loc
    
    if len(solutions) != 0:
        indice = random.randint(0, len(solutions) - 1)
        return solutions[indice] 
    else:
        return np.array([])

def tabou(XY, max_depl, n, tabou_size):
    # solution initiale au hasard
    start = time.process_time()
    solution = init_solution(n)
    print(f"MAX_DEPL {max_depl} -> tabou size = {tabou_size}")

    # initialise la liste tabou
    Tabou = []

    msol = solution
    nb_depl = 0
    STOP = False

    while (nb_depl < max_depl) and (not STOP):
        voisin = meilleur_voisin_non_tabou(XY, Tabou, solution, n)
        if len(voisin) == 0:
            STOP = True
        else:
            Tabou.append(solution)
            if meilleur(voisin, msol, XY, n):
                msol = voisin
            solution = voisin
            nb_depl += 1
            if len(Tabou) > tabou_size:
                Tabou.pop(0)

    end = time.process_time()
    print(f"Valeur du Solution finale = {calculer_solution(XY,msol,n)} en {end-start} scs (nombre de déplacements = {nb_depl})")


if len(sys.argv) != 6:
    print("python 3 voyageurDeCommerce.py Instance Name, SIZE, MAX_DEPL, MAX_ESSAIE, ALGO")
    sys.exit(1)

XY, n = lire_instance(sys.argv[1])
SIZE, MAX_DEPL, MAX_ESSAIE, ALGO = int(sys.argv[2]), int(sys.argv[3]), int(sys.argv[4]), int(sys.argv[5])


if ALGO == 1:
    hill_climbing_red(XY, MAX_ESSAIE, n, MAX_DEPL)
else:
    tabou(XY, MAX_DEPL, n, SIZE)








