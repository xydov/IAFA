      .global     _start
_start:
      mov r0,r1

_exit:
  	@ Retour a Angel par exception (appel systeme)
      mov   r0, #0x18
      ldr   r1, =0x20026
      swi 	0x123456
