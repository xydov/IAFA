# Sequential version
# python3 n-bodies-base.py 12 1000

import sys
import math
import random
import matplotlib.pyplot as plt
import time
import numpy as np

ID, POSX, POSY, SPEEDX, SPEEDY, WEIGHT = range(6)

def split(x, size):
	n = math.ceil(len(x) / size)
	return [x[n*i:n*(i+1)] for i in range(size-1)]+[x[n*(size-1):len(x)]]


def unsplit(x):
	y = []
	n = len(x)
	for i in range(n):
		for j in range(len(x[i])):
			y.append(x[i][j])
	return y

solarmass=1.98892e30
def circlev(rx, ry):
    r2=math.sqrt(rx*rx+ry*ry)
    numerator=(6.67e-11)*1e6*solarmass
    return math.sqrt(numerator/r2)
# from http://physics.princeton.edu/~fpretori/Nbody/code.htm
def create_item(id, positionx, positiony, speedx, speedy, weight):
    if positionx == 0 and positiony == 0:  # the center of the world, very heavy one...
        speedx = 0
        speedy = 0
    else:
        if speedx==0 and speedy==0:            # initial values
            magv=circlev(positionx, positiony)
            absangle = math.atan(math.fabs(positiony/positionx))
            thetav= math.pi/2-absangle
            phiv = random.uniform(0,1)*math.pi
            speedx = -1*math.copysign(1, positiony)*math.cos(thetav)*magv
            speedy = math.copysign(1, positionx)*math.sin(thetav)*magv
            #Orient a random 2D circular orbit
            if (random.uniform(0,1) <=.5):
                speedx=-speedx
                speedy=-speedy
    return np.array([id, positionx, positiony, speedx, speedy, weight], dtype='f')

def str_item(item):
    return "ID="+str(item[ID])+" POS=("+str(item[POSX])+","+str(item[POSY])+") SPEED=("+str(item[SPEEDX])+","+str(item[SPEEDY])+") WEIGHT="+str(item[WEIGHT])

def display(m, l):
    for i in range(len(l)):
        print("PROC"+str(rank)+":"+m+"-"+str_item(l[i]))

def displayPlot(d):
    plt.gcf().clear()            # to remove to see the traces of the particules...
    plt.axis((-1e17,1e17,-1e17,1e17))
    xx = [ d[i][POSX]  for i in range(len(d)) ]
    yy = [ d[i][POSY]  for i in range(len(d)) ]
    plt.plot(xx, yy, 'ro')
    plt.draw()
    plt.pause(0.00001)            # in order to see something otherwise too fast...


def interaction(i, j):
    dist = math.sqrt( (j[POSX]-i[POSX])*(j[POSX]-i[POSX]) +  (j[POSY]-i[POSY])*(j[POSY]-i[POSY]) )
    if dist == 0:
        return np.zeros(2)
    g = 6.673e-11
    factor = g * i[WEIGHT] * j[WEIGHT] / (dist*dist+3e4*3e4)
    return np.array([factor*(j[POSX]-i[POSX])/dist, factor*(j[POSY]-i[POSY])/dist])

def update(d, f):
    dt = 1e11
    vx = d[SPEEDX] + dt * f[0]/d[WEIGHT]
    vy = d[SPEEDY] + dt * f[1]/d[WEIGHT]
    px = d[POSX] + dt * vx
    py = d[POSY] + dt * vy
    return create_item(d[ID], positionx=px, positiony=py, speedx=vx, speedy=vy, weight=d[WEIGHT])

def signature(world):
    s = 0
    for d in world:
        s+=d[POSX]+d[POSY]
    return s

def init_world(n):
    data = [ create_item(id=i, positionx=1e18*math.exp(-1.8)*(.5-random.uniform(0,1)), positiony=1e18*math.exp(-1.8)*(.5-random.uniform(0,1)), speedx=0, speedy=0, weight=(random.uniform(0,1)*solarmass*10+1e20)) for i in range(n-1)]
    data.append( create_item(id=nbbodies-1, positionx=0, positiony=0, speedx=0, speedy=0, weight=1e6*solarmass))
    return np.array(data)

nbbodies = int(sys.argv[1])
NBSTEPS = int(sys.argv[2])
DISPLAY = len(sys.argv) != 4








"""
for t in range(NBSTEPS):
	force = []
	for i in range(nbbodies):
		force.append((0,0)) # force[i]
		for j in range(nbbodies):
			[dfx, dfy] = interaction(data[i], data[j])
			[fx, fy] = force[i]
			force[i] = [fx + dfx, fy + dfy]

	for i in range(nbbodies):
		data[i] = update(data[i], force[i])
"""
"""
for t in range(NBSTEPS):
	force = []
	for i in range(nbbodies):
		force.append((0,0)) # force[i]
		for j in range(nbbodies):
			force[i]+=interaction(data[i] , data[j])

	for i in range(nbbodies):
		data[i] = update(data[i], force[i])

"""

from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

if(rank == 0):
	random.seed(0)   
	data = init_world(nbbodies)
	data_split = split(data, size)
	start = time.time()
else:
	data = None
	data_split = None

data_split = comm.scatter(data_split, root=0)
data = comm.bcast(data, root=0)  # global data
n = math.ceil(len(data) / size)

for t in range(NBSTEPS):

    force = np.zeros((len(data), 2))
    for i in range(len(data_split)):
        for j in range(rank * n + i):
            [dfx, dfy] = interaction(data_split[i], data[j])
            [fx_i, fy_i] = force[rank * n + i]
            [fx_j, fy_j] = force[j]
            force[rank * n + i] = [fx_i + dfx, fy_i + dfy]
            force[j] = [fx_j - dfx, fy_j - dfy]

    force = comm.allreduce(force, op=MPI.SUM)
    for i in range(len(data_split)):
        data_split[i] = update(data_split[i], force[rank * n + i])

    data = unsplit(comm.allgather(data_split))
    data_split = split(data, size)[rank]


if(rank == 0):
 
    print("time : " + str(time.time()-start))
    print(str(signature(data)))
