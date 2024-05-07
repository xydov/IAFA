import tsplib95
import os
import time
import random, numpy, math, copy, matplotlib.pyplot as plt
import itertools

def euclidean_2d(a, b):
    x1, y1 = a
    x2, y2 = b
    dist = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
    return dist #* random.random() * 2

def dist(problem):
    nodeList = list(problem.get_nodes())
    for i in nodeList:
        for j in nodeList[:i]:
            print(problem.wfunc(i, j),end=" ")
        print("\n")
    
def longtour(t):
    l=0
    for i in range(len(t)-1):
        #print(problem.wfunc(t[i], t[i+1]))
        l=l+problem.wfunc(t[i], t[i+1])
    l=l+problem.wfunc(t[len(t)-1], t[0])
    return l

def longtour_zero(t):
    l=0
    for i in range(len(t)-1):
        #print(problem.wfunc(t[i], t[i+1]))
        l=l+problem.wfunc(t[i], t[i+1])
    l=l+euclidean_2d((0,0), (problem.get_display(t[0])[0],problem.get_display(t[0])[1]))
    l=l+euclidean_2d((problem.get_display(t[-1])[0],problem.get_display(t[-1])[1]),(0,0))
    return l

def brute(problem):
    L = list(itertools.permutations(problem.get_nodes()))
    min = longtour(list(L[0]))
    minp=[]
    for i in L:
        p = list(i)
        lg = longtour(p)
        if lg<min:
            min = lg
            minp = p
    return minp,min

def recuit(problem):
    c = problem.node_coords
    cl = list(c.values())
    cities = []
    long = len(cities)
    for i in cl:
        cities.append(list(i))
    long = len(cities)
    tour = random.sample(range(1,long+1),long); 
    #print("tour=",tour)
    #print("Cities=",cities,"long=",long,"len=",len(cities))
    for temperature in numpy.logspace(0,5,num=100000)[::-1]:
        [i,j] = sorted(random.sample(range(long),2));
        newTour =  tour[:i] + tour[j:j+1] +  tour[i+1:j] + tour[i:i+1] + tour[j+1:];  
        if math.exp((sum([math.sqrt(sum([(cities[tour[(k+1) % long]-1][d] - cities[tour[k % long]-1][d])**2 for d in [0,1]])) for k in [j,j-1,i,i-1]]) - sum([ math.sqrt(sum([(cities[newTour[(k+1) % long]-1][d] - cities[newTour[k % long]-1][d])**2 for d in [0,1] ])) for k in [j,j-1,i,i-1]])) / temperature) > random.random():
            tour = copy.copy(newTour);
    #plt.plot([cities[tour[i % long]-1][0] for i in range(long+1)], [cities[tour[i % long]-1][1] for i in range(long+1)], 'xb-');
    return(tour)
    
def takeThird(elem):
    return elem[2]

def graphe(problem,tour,c):
    long = len(problem)
    plt.plot([problem.get_display(tour[i % long])[0] for i in range(long+1)], [problem.get_display(tour[i % long])[1] for i in range(long+1)], 'x'+c+'-');
    plt.show()
    
os.chdir("../Code C/")
print("Répertoire : ",os.getcwd())
problem = tsplib95.load_problem("Data/att48.tsp")


start = time.time()
res = recuit(problem)
end = time.time()
print("recuit=",res)
print("long=",longtour(res))
print("Tps=",end-start)
graphe(problem,res,'b')