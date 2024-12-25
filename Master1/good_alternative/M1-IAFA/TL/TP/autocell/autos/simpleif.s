	.meta source "\"autos/simpleif.auto\""
	.meta fields "[{ \"name\": \"\", \"num\": 0, \"lo\": 0, \"hi\": 1 }]"
	invoke 1, 2, 3
	seti r4, #1
	seti r0, #0
L0:
	seti r1, #0
L1:
	invoke 3, 0, 1
	invoke 5, 14, 6
	set r5, r14
	invoke 5, 13, 2
	set r6, r13
	goto_ne L8, r5, r6
L9:
	seti r12, #1
	invoke 4, 12, 0
	goto L10
L8:
L10:
	add r11, r5, r6
	seti r10, #2
	goto_eq L2, r11, r10
L3:
	invoke 5, 9, 3
	invoke 5, 8, 5
	goto_ge L4, r9, r8
L5:
	seti r7, #2
	invoke 4, 7, 0
	goto L6
L4:
L6:
	goto L7
L2:
L7:
	add r1, r1, r4
	goto_lt L1, r1, r3
	add r0, r0, r4
	goto_lt L0, r0, r2
	stop
