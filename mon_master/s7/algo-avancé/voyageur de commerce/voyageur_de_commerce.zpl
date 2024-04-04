#read input file
param fichier := "tsp5.txt";

# Read the number of cities from the file
param C := read fichier as "1n" use 1;
do print "Number of cities: ", C;

# Set of cities
set V := {read fichier as "<1n>" skip 1, <0>};


# Coordinates of cities
param px[V] := read fichier as "<1n> 2n" comment "#" skip 1, <0> 0;
param py[V] := read fichier as "<1n> 3n" comment "#" skip 1, <0> 0;

# Binary variable matrix to represent tours
var K[V*V] binary;

# Integer variable array to model subtour elimination
var U[V] integer >= 0;

# Function to calculate the Euclidean distance between two cities
defnumb distance_euc(i, j) := sqrt((px[j] - px[i])^2 + (py[j] - py[i])^2);


# Objective: minimize the total distance
minimize distance: sum <i, j> in V * V : distance_euc(i, j) * K[i, j];

# Constraints
subto each_city_arrival:
  forall <j> in V : sum <i> in V with j != i : K[j, i] == 1;

subto subtour_elimination:
  forall <i> in V : forall <j> in V with j != 0 : U[i] - U[j] + C * K[i, j] <= C - 1;

subto each_city_departure:
  forall <j> in V : sum <i> in V with j != i : K[i, j] == 1;



#contraints test
#subto one_departure_per_city: forall <i> in V : sum <j> in V with i != j : x[i, j] == 1;

#subto no_subtour: forall <k> in K with card(P[k]) > 2 and card(P[k]) < card(V) - 2 :sum <i, j> in E with <i> in P[k] and <j> in P[k] : x[i, j] <= card(P[k]) - 1;

#subto c3: forall <i> in V : forall <j> in V with j != 0 :U[i] - U[j] + C * Voy[i, j] <= C - 1;




