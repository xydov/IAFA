#! /usr/bin/python3

import time
import random
import functools
import matplotlib.pyplot as plt

def init_matrix(size_x, size_y):
    result = []
    for _ in range(size_x):
        result.append([0]*size_y)
    return result

def print_matrix(matrix):
    size_x = len(matrix)
    size_y = len(matrix[0])
    for y in range(size_y):
        for x in range(size_y):
            print(matrix[x][y], end=' ')
        print()

def add_hot_spots(matrix, number):
    size_x = len(matrix)
    size_y = len(matrix[0])

    for i in range(number):
        x = random.randrange(1, size_x-1)
        y = random.randrange(1, size_y-1)
        matrix[x][y] = random.randint(500, 1000)


def get_val(matrix, x, y):
    tmp = matrix[x][y] + matrix[x-1][y] + matrix[x+1][y] + matrix[x][y-1] + matrix[x][y+1]
    return tmp // 5


def get_signature(matrix):
    return functools.reduce(lambda a,b: a^b, [sum(col) for col in matrix])

if __name__ == '__main__':

    random.seed(3)
    
    width = 100
    
    matrix = init_matrix(width, width)
    add_hot_spots(matrix, 400)

    init_time = time.time()

    tmp_matrix = init_matrix(width, width)

    for _ in range(20):
        for x in range(1, width-1):
            for y in range(1, width-1):
                tmp_matrix[x][y] = get_val(matrix, x, y)
        matrix, tmp_matrix = tmp_matrix, matrix
    
    final_time = time.time()
    print('Total time:', final_time-init_time, 's')
    print('Signature:', get_signature(matrix))
    plt.imshow(matrix, cmap='hot', interpolation='nearest')
    plt.colorbar()

    plt.savefig('heat.pdf')  
    plt.show(block=True)
