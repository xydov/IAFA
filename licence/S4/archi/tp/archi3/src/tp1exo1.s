.global _start

_start: cmp r2,r1
        movhi r3,r2
        movls r3,r1

_exit: b _exit
