.global _start

tab: .int 9, -4, 27592, 0, -27592, 9, -4, 27592, 0, -27592

_start:
            mov r3,#0 @ addresse max
            mov r6,#0 @ valeur du max
            mov r1,#0 @ i

            adr r5,tab
tq:         cmp r1,#10
            bge fin
            ldr r2, [r5, r1, LSL #2]

            ldr r6, [r5, r3, LSL #2]
            @ je récupère la valeur de r3 dans r6
            cmp r6,r2
            @ je compare r6 et r2
            bge next
            @ si r2 > r6 je met dans r3, r1
            mov r3,r1

            @ not needed str r2, [r5, r1, LSL #2]
next:       add r1,r1,#1     @ i = i + 1
            b tq
            b fin
fin:
_exit: b _exit
