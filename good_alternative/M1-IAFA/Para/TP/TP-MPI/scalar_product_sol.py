# /usr/bin/python3

# mpirun -n 2 python3 scalar_product_sol.py 6

from mpi4py import MPI
import random
import sys

def scalar_product(X, Y):
    result = 0
    for i in range(len(X)):
        result += X[i]*Y[i]
    return result


# split a vector "x" in "size" part assuming len(x)%size == 0
def split(x, size):
    n = len(x) // size
    return [x[n*i:n*(i+1)] for i in range(size)]

# split a vector "x" in "size" part, no assumption
def split2(x, size):
    n = len(x) // size
    if len(x) % size != 0:
        n+= 1

    return [x[n*i:n*(i+1)] for i in range(size)]

   
if __name__ == '__main__':
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()


    if rank == 0:
        random.seed(0)
        #read from command line
        nb_elem = int(sys.argv[1])    #length of vectors

        x = [random.random() for _ in range(nb_elem)]
        y = [random.random() for _ in range(nb_elem)]
        print ("X=", x)
        print ("Y=", y)
        
        # Version 1 : pas de problème de modulo
        xsplitted = split2(x, size)
        ysplitted = split2(y, size)
        print("Xsplitted=", xsplitted)
        print("Ysplitted=", ysplitted)
    else:
        xsplitted = None
        ysplitted = None

    # scatter the vector to the other nodes 
    local_x = comm.scatter(xsplitted, root=0)
    local_y = comm.scatter(ysplitted, root=0)
    print("Processus ", rank, "has vector X=", local_x, "and Y=", local_y)

    #local computation of dot product
    local_dot = scalar_product(local_x, local_y)
    print("Processus ", rank, "has local_dot=", local_dot)

    #sum the results of each
    dot = comm.reduce(local_dot, op = MPI.SUM, root=0)
    
    if (rank == 0):
        print ("The dot product is", dot, "computed in parallel")
        
