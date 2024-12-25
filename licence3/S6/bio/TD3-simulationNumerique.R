# script simulation EDO n>1
# L3 Dyn Pop pour informaticien
# encodage: utf-8
# faire le ménage
rm(list=ls())
# paramètres:
library(deSolve) # install.packages("deSolve", dependencies=T)
# parametres du systeme
r1=0.8
r2=0.8
K1 = 500
K2 = 500
alpha  = 0.5
beta = 0.7

valsN1 = seq(0,1000, by = 1)
# isocline de dN1/dt
isoN1 = (K1 - valsN1)/alpha # N2 = (K1-N1)/alpha
plot(isoN1 ~ valsN1, col='red', ylim = c(0,1000), type='l', 
     xlab = "Population 1", ylab="Population 2", main="Compétition VL: coexistence")
abline(v=0, col='red')
# isocline de dN2/dt
isoN2 = K2 - beta* valsN1 # K2 - beta*N1
lines(isoN2 ~ valsN1, col='blue')
abline(h=0, col='blue')

# ajouter une trajectoire
library(deSolve)
n10 = 220
n20 = 900
compVL = function(t, x, parms) { # les paramètres sont des variables globales
  n1 = x[1]
  n2 = x[2]
  dn1dt = r1*(1-(n1+alpha*n2)/K1)*n1
  dn2dt = r2*(1-(n2+beta*n1)/K2)*n2
  return(list(c(dn1dt,dn2dt)))
}
Tfin = 25
lesT = seq(0, Tfin, by=0.1)
sol = ode(c(n10,n20), lesT, compVL, c(0))
lines(sol[,3] ~ sol[,2], col="black")

n10 = 900
n20 = 220
sol = ode(c(n10,n20), lesT, compVL, c(0))
lines(sol[,3] ~ sol[,2], col="black")
