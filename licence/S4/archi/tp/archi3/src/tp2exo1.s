.global _start


operateur: .byte '*' @ peut aussi contenir '*' ou '+'
 .align

_start:
      mov r1,#5
      mov r2,#4
      adr r5, operateur
      ldrb r4,[r5]
back: cmp r4,#'+'
      beq plus
next: cmp r4,#'-'
      beq moins
nm: cmp r4,#'*'
      beq mult
      b _exit

plus: add r3,r1,r2
      b next

moins:
      sub r3,r1,r2
      b nm
mult:
      mul r3,r1,r2
      b _exit
_exit: b _exit
