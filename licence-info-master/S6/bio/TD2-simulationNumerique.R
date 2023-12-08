# script simulation equation effet allee 
# L3 Dyn Pop pour informaticien
# encodage: utf-8
# faire le ménage
rm(list=ls())
# paramètres:
r = 1.5
K = 100
E = 10
T = 5
dt= 0.1
lesT = seq(0, T, by = dt)
N0 = 2
popT = rep(0, length(lesT))
popT[1] = N0
# implémentation méthode d'Euler
for (i in 2:length(lesT)) {
  popT[i] = popT[i-1] + dt*r*popT[i-1]*(1-popT[i-1]/K)*(popT[i-1]/E - 1)
}
plot(popT ~ lesT, type="l", ylim=c(0, K+10), main="Croissance type Allee",
     xlab="Temps (min)", ylab="Effectif (nombres d'individus)")
# ajouter une dynamique avec N0 > E
N0 = 12
popT[1] = N0
# implémentation méthode d'Euler
for (i in 2:length(lesT)) {
  popT[i] = popT[i-1] + dt*r*popT[i-1]*(1-popT[i-1]/K)*(popT[i-1]/E - 1)
}
lines(popT ~ lesT, col="tomato")
# ajouter une dynamique avec N0 > K
N0 = K+10
popT[1] = N0
# implémentation méthode d'Euler
for (i in 2:length(lesT)) {
  popT[i] = popT[i-1] + dt*r*popT[i-1]*(1-popT[i-1]/K)*(popT[i-1]/E - 1)
}
lines(popT ~ lesT, col="blue")

# la méthode d'Euler n'est ni précis ni efficace
# utilisons une méthode type Runge-Kutta Fehlberg
library(deSolve) # install.packages("deSolve", dependencies=T)
help(ode)
allee = function(t, x, paras) {
  # parametres: (rr, EE, KK) 
  rr = paras[1]
  EE = paras[2]
  KK = paras[3]
  dNdt = rr*x*(1-x/KK)*(x/EE-1)
  return(list(dNdt))
}
# format ode(conditioninitiale, vecteursT, func, paras)
solution = ode(y=12, times = lesT, func=allee, parms=c(r, E, K))
lines(solution[,2] ~ solution[,1], col="tomato", lty='dashed', lwd=2)

solution = ode(y=2, times = lesT, func=allee, parms=c(r, E, K))
lines(solution[,2] ~ solution[,1], col="black", lty='dashed', lwd=2)

solution = ode(y=K+10, times = lesT, func=allee, parms=c(r, E, K))
lines(solution[,2] ~ solution[,1], col="blue", lty='dashed', lwd=2)
legend(2,60, legend=c("Euler","Runge-Kutta-Fehlberg"), 
       lty=c("solid", "dashed"), col=c("black","black"))
