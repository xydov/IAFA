#mpirun -n 4 python3 over_mean.py 20
from mpi4py import MPI
import sys
import random

# split a vector "x" in "size" part, no assumption
def split(x, size):
    n = len(x) // size
    if len(x) % size != 0:
        n+= 1

    return [x[n*i:n*(i+1)] for i in range(size)]

	
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

#read from command line
n = int(sys.argv[1])    #length of vectors

#arbitrary example vectors, generated to be evenly divided by the number of
#processes for convenience
data = None

splitted_data = None

if rank == 0:
    random.seed(0)
    data = [random.randint(1, 100) for _ in range(n)]
    print ("Data =", data)

    #divide up the vector
    splitted_data = split(data, size)
    print("splitted data =", splitted_data)

# scatter the vector to the other nodes 
local_data = comm.scatter(splitted_data, root=0)

print("Processus ", rank, "has vector data =", local_data)

#local computation of local sum
local_sum = sum(local_data)
print("Processus ", rank, "has local_sum =", local_sum)

total_sum = comm.allreduce(local_sum, op = MPI.SUM)
global_mean = total_sum / (len(local_data) * size)

print("Processus ", rank, "has global_mean =", global_mean)

local_count = len([val for val in local_data if val >= global_mean])

#sum the results of each
global_count = comm.reduce(local_count, op = MPI.SUM, root=0)

if (rank == 0):
    print ("The number of value over the mean is", global_count)
