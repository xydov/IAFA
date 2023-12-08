
.global _start

_start:

chaine: .asciz  "#ABZ]aez}"

          adr r7,chaine
          mov r1,#0
tq:       cmp r6,#'0'
          bhs fin
          ldr r2,[r7, r1, LSL #2]@ load ldrb
          add r2,r2,#1
          str r2,[r7, r1, LSL #2]  @ write strb
          add r1,r1,#1 @ i = i + 1
          b tq
          b fin
fin:

_exit: b _exit
