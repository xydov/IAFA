print("hello world")

# croissance exponentielle discrte, N_{t+1} = N_{t}*R
temps = 10 # cycles de reproduction
dt = 1
N = rep(0, temps+1)
N0 = 1
R = 2
N[1] = N0
for (i in 2:length(N)) {
  N[i] = N[i-1] * R
}
lesTemps = seq(0,temps, by=1) # seq = sequence
plot(N ~ lesTemps, xlab = "Temps (générations)", 
     ylab="Effectif N(t)", 
     main = "Croissance expontielle discrete", type ='b')
# help(par) aide sur les paramètres des graphiques

# croissances exponentielle, dN/dt = rN, N(0) = N0
Nc = rep(0, temps+1)
Nc[1] = N0
r = 1.5  # correspondance: R = exp(r) <-> log(R) = r
r = log(R) # log Neperien
# solution de l'EDO: N0*exp(r*t)
for (i in 1:length(Nc)) {
  Nc[i] = N0*exp(r * lesTemps[i])
}
lines(Nc ~ lesTemps, col= "red")

plot(N ~ lesTemps, xlab = "Temps (générations)", 
     ylab="Effectif N(t)", 
     main = "Croissance expontielle discrete", type ='b')
dt = 0.01
lesTempsFine = seq(0, temps, by = dt)
NcFine = rep(0, length(lesTempsFine))
for (i in 1:length(NcFine)) {
  NcFine[i] = N0*exp(r * lesTempsFine[i])
}
lines(NcFine ~ lesTempsFine, col= "red")

# croissance logistique discrete, N_{t+1} = N_{t}*exp(r*(1-N_{t}/K))
temps = 1000 # cycles de reproduction
dt = 1
N = rep(0, temps+1)
N0 = 1
r = 2.73 # r=2: oscillations quasiment plus amortie
# r < 1: croissance sigmoide
# 1 < r < 2: oscillations amorties vers équilibre stable
# 2 < r < 2.5 : 2-cycles
# 2.5 < r < 2.65: 4-cycles
# 2.65< r < 2.67: 8-cycles
# ....
# 2.71 < r < ...: apériodicité, dynamiques en chaos déterministe
K = 30
N[1] = N0
for (i in 2:length(N)) {
  N[i] = N[i-1] * exp(r*(1-N[i-1]/K))
}
lesTemps = seq(0,temps, by=1) # seq = sequence
plot(N ~ lesTemps, xlab = "Temps (générations)", 
     ylab="Effectif N(t)", 
     main = "Croissance logistique discrete", type ='b')
