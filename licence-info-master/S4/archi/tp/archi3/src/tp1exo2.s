.global _start

_start:
      mov r4,#0 @ r
      mov r5,#48 @ a
      mov r6,#18 @ b

bcl:  cmp r6,#0
      beq fin

      mov r4,r5
in_bcl:   cmp r4,r6
          blo in_fin

          sub r4,r4,r6
          b in_bcl
in_fin:

      mov r5,r6
      mov r6,r4
      b bcl

fin:  mov r7,r5 @ r7 = pgcd

_exit: b _exit
