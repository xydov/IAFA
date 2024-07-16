	.meta source "\"autos/addsub.auto\""
	.meta fields "[{ \"name\": \"\", \"num\": 0, \"lo\": 0, \"hi\": 9 }]"
	invoke 1, 2, 3
	seti r4, #1
	seti r0, #0
L0:
	seti r1, #0
L1:
	invoke 3, 0, 1
	invoke 5, 15, 6
	seti r16, #1
	add r15, r15, r16
	set r5, r15
	seti r14, #1
	sub r14, r5, r14
	invoke 4, 14, 0
	seti r12, #5
	sub r12, r12, r5
	invoke 5, 13, 6
	sub r12, r12, r13
	set r6, r12
	seti r10, #5
	add r10, r10, r5
	invoke 5, 11, 6
	sub r10, r10, r11
	set r7, r10
	seti r8, #5
	sub r8, r8, r5
	invoke 5, 9, 6
	add r8, r8, r9
	invoke 4, 8, 0
	add r1, r1, r4
	goto_lt L1, r1, r3
	add r0, r0, r4
	goto_lt L0, r0, r2
	stop
