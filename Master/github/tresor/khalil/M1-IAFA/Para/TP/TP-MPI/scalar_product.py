# /usr/bin/python3

# python3 scalar_product.py 20

import random
import sys

def scalar_product(X, Y):
    result = 0
    for i in range(len(X)):
        result += X[i]*Y[i]
    return result

if __name__ == '__main__':

    random.seed(0)
    #read from command line
    nb_elem = int(sys.argv[1])    #length of vectors

    X = [random.random() for _ in range(nb_elem)]
    Y = [random.random() for _ in range(nb_elem)]

    result = scalar_product(X, Y)
    print(result)
