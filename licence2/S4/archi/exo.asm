.global _start
chaine: .asciz "blablabla"
_start: mov r1,#0

    mov r3, #0
    adr r4,chaine
tq: ldrb r5,[r4],#1
    cmp r5,#0
    beq fin
    cmp r5,#'a'
    bne incr
    cmp r1,#0
    moveq r2,r3
    add r1,r1,#1
incr: add r3,r3,#1
    b tq



atoi


entier = 0
ptr == chaine
while (*ptr != 0)
{
    entier *= 10;
    entier += (*ptr - '0);
    ptr ++;
}

main:       adr r3,chaine
            mov r1,#0
tq            ldrb r2,[r3],#1
            cmp r2,#0
            beq ftq

            add r1,r1,r1, lsl #2
            add r1,r1,r1

            sub r2,r2,#'0'
            add r1,r1,r2
            b tq
ftq