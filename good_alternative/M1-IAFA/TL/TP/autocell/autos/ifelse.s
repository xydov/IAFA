	.meta source "\"autos/ifelse.auto\""
	.meta fields "[{ \"name\": \"\", \"num\": 0, \"lo\": 0, \"hi\": 1 }]"
	invoke 1, 2, 3
	seti r4, #1
	seti r0, #0
L0:
	seti r1, #0
L1:
	invoke 3, 0, 1
	invoke 5, 19, 6
	set r5, r19
	invoke 5, 18, 2
	set r6, r18
	goto_ne L11, r5, r6
L12:
	seti r17, #1
	invoke 4, 17, 0
	goto L13
L11:
	seti r16, #0
	invoke 4, 16, 0
L13:
	add r15, r5, r6
	seti r14, #2
	goto_eq L2, r15, r14
L3:
	invoke 5, 13, 3
	invoke 5, 12, 5
	goto_ge L7, r13, r12
L8:
	seti r11, #2
	invoke 4, 11, 0
	goto L9
L7:
	seti r10, #0
	invoke 4, 10, 0
L9:
	goto L10
L2:
	invoke 5, 9, 0
	seti r8, #0
	goto_ne L4, r9, r8
L5:
	seti r7, #1
	invoke 4, 7, 0
	goto L6
L4:
L6:
L10:
	add r1, r1, r4
	goto_lt L1, r1, r3
	add r0, r0, r4
	goto_lt L0, r0, r2
	stop
