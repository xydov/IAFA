import sys
import random

#read from command line
n = int(sys.argv[1])    #length of vectors

random.seed(0)
data = [random.randint(1, 100) for _ in range(n)]
print ("Data =", data)

total_sum = sum(data)
global_mean = total_sum / (len(data))
count = len([val for val in data if val >= global_mean])

print ("The number of value over the mean is", count)
