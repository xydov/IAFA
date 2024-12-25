	.meta source "\"autos/neg.auto\""
	.meta fields "[{ \"name\": \"\", \"num\": 0, \"lo\": 0, \"hi\": 1 }]"
	invoke 1, 2, 3
	seti r4, #1
	seti r0, #0
L0:
	seti r1, #0
L1:
	invoke 3, 0, 1
	seti r11, #0
	invoke 5, 13, 6
	sub r11, r11, r12
	set r5, r11
	seti r10, #0
	sub r10, r10, r5
	set r6, r10
	seti r7, #0
	add r9, r5, r6
	sub r7, r7, r8
	invoke 4, 7, 0
	add r1, r1, r4
	goto_lt L1, r1, r3
	add r0, r0, r4
	goto_lt L0, r0, r2
	stop
