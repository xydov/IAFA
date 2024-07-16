	.meta source "\"autos/expr.auto\""
	.meta fields "[{ \"name\": \"\", \"num\": 0, \"lo\": 0, \"hi\": 9 }]"
	invoke 1, 2, 3
	seti r4, #1
	seti r0, #0
L0:
	seti r1, #0
L1:
	invoke 3, 0, 1
	invoke 5, 5, 0
	invoke 5, 6, 5
	invoke 5, 7, 7
	add r6, r6, r7
	invoke 5, 8, 3
	add r6, r6, r8
	invoke 5, 9, 1
	add r6, r6, r9
	seti r10, #3
	mod r6, r6, r10
	add r5, r5, r6
	seti r11, #9
	mod r5, r5, r11
	invoke 4, 5, 0
	add r1, r1, r4
	goto_lt L1, r1, r3
	add r0, r0, r4
	goto_lt L0, r0, r2
	stop
