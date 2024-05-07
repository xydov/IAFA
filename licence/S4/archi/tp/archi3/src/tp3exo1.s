.global _start

tab: .int 9, -4, 27592, 0, -27592, 9, -4, 27592, 0, -27592

_start:
          @ r1 = reg entrée
          @ r0 = reg sortie == |r1|
          @ r5 = somme des val abs
          @r2 = i
          
          mov r0,#0
          mov r2,#0
          mov r5,#0

          adr r3,tab

tq:       cmp r2,#10   @start bcl
          bge _exit
          @put first tab value into r1
          ldr r1, [r3, r2, LSL #2]
          mov r0,r1
          bl abs
          add r5,r5,r0
          add r2,r2,#1
          @end bcl
          b tq
          b _exit



abs:      cmp r1,#0
          bgt end_abs
          rsb r0,r1,#0
end_abs:  mov pc,lr


_exit: b _exit
