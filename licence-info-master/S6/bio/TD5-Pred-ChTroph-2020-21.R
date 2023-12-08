# script analyse par isoclines des equations de prédation Volterra-Lotka 
# L3 Dyn Pop pour informaticien
# encodage: utf-8
# faire le ménage
rm(list=ls())
# parametres
r = 1.0
a = 2.0
e = 0.1
mu = 0.3
r/a # equilibre non-trivial prédateur
mu/(e*a) # équilibre non-trivial proie
# tracer les isoclines
plot(0 ~ 0, main="Prédation Lotka-Volterra", xlab="N", ylab="P",
     xlim = c(0,4), ylim=c(0,1.0), col="black", type="l")
abline(v=0, col="red") # ou N = 0
abline(h=r/a, col="red") # P = r/a
abline(h=0, col="blue") # ou P = 0
abline(v=mu/(e*a), col="blue") # N = mu/(e a)
points(0,0,pch=1)
points(mu/(e*a), r/a, pch=1)
legend('topright', legend=c("iso N","iso P", "equilibre"), lty=c(1,1,0),
       col=c('red','blue','black'), pch=c(NA,NA,1))
arrows(3,0.8,3,0.95,col="blue")
arrows(3,0.1,3,0.25,col="blue")
arrows(0.8, 0.95, 0.8,0.8,col="blue")
arrows(0.5, 0.25, 0.5, 0.1,col="blue")
arrows(3,0.8,2.5,0.8,col="red")
arrows(3,0.1,3.5,0.1,col="red")
arrows(0.8,0.95,0.3,0.95,col="red")
arrows(0.5,0.25,0.9,0.25,col="red")
# ajouter une trajectoire
library(deSolve)
predLV = function(t, x, parms) { # les paramètres sont des variables globales
  n = x[1]
  p = x[2]
  dndt = r*n - a*n*p
  dpdt = e*a*n*p - mu*p
  return(list(c(dndt,dpdt)))
}
Tfin = 25
lesT = seq(0, Tfin, by=0.1)
N0P0 = c(2,0.3)
sol = ode(N0P0, lesT, predLV, c(0))
lines(sol[,3] ~ sol[,2], col="gray", lwd=2)
points(N0P0, col="gray")
text(N0P0,"Condition\ninitiale", pos=1)

# Dynamique en fonction du temps
plot(sol[,2] ~ sol[,1], xlab="Temps", ylab="Effectif", 
     main="Prédation Lotka-Volterra", type="l", col="red", lwd=2, ylim=c(0,4.0))
lines(sol[,3] ~ sol[,1], col="blue", lwd=2)
legend('topleft', legend=c("N(t)","P(t)"), lty=c(1,1),
       col=c('red','blue'), ,lwd=2)
