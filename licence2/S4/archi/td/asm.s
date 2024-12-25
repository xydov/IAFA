@itoa sous programme imbriqués

main:       adr r0,val
            ldr r0,[r8]
            adr r1,chaine
            bl itoa
exit:       b exit

.equ N,4
val:        .int 1234
chaine:     .fill N+1,1
            .align

itoa: @ sous-programme
    @r0 doit contenir val
    @r1 doit contenir ptr sur chaine
    stmfd sp!,{r0-r4}
    add r1,r1,#N
    mov r4,#0 @ r4 = i
    strb 