.global _start

.eqn N, 286

_start:
      mov r1,#0 @ r1 : somme 2
      mov r2,#0 @ r2 : somme 4
      mov r3,#0 @ r3 : somme 8
      mov r4,#0 @ r4 : i
      

_exit: b _exit
