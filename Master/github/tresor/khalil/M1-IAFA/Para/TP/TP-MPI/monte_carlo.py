#! /usr/bin/python3

import time
import random

if __name__ == '__main__':
    nb = 100001
    inside = 0
    
    start_time = time.time()
    for _ in range(nb):
        x = random.random()
        y = random.random()
        if x*x + y*y <= 1:
            inside +=1
    end_time = time.time()
    print("Pi =", 4 * inside/nb, "in ", end_time-start_time, 'seconds')
