# mpirun -n 2 python3 ./test_mpi.py

from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

print("rank :", rank)
print("size :", size)
