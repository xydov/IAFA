r = 2.2
K = 100
N0 = 2
Ttot = 90
lesR = seq(1, 3, by=0.01)
plot(1,N0, xlim=range(lesR), ylim=c(0,250), type='l', xlab="valeur de r", ylab='effectif')
for (r in lesR) {
  pop = rep(0, Ttot + 100)
  pop[1] = N0
  for (gen in 2:length(pop)) {
    pop[gen] = pop[gen-1]*exp(r*(1-pop[gen-1]/K))
  }
  for (gen in length(pop):(length(pop)+100)) {
    gen = gen+1
    pop[gen] = pop[gen-1]*exp(r*(1-pop[gen-1]/K))
    points(r,pop[length(pop)],pch=20)
  }
}