	.meta source "\"autos/conway.auto\""
	.meta fields "[{ \"name\": \"\", \"num\": 0, \"lo\": 0, \"hi\": 1 }]"
	invoke 1, 2, 3
	seti r4, #1
	seti r0, #0
L0:
	seti r1, #0
L1:
	invoke 3, 0, 1
	invoke 5, 14, 2
	invoke 5, 15, 1
	add r14, r14, r15
	invoke 5, 16, 8
	add r14, r14, r16
	invoke 5, 17, 7
	add r14, r14, r17
	invoke 5, 18, 6
	add r14, r14, r18
	invoke 5, 19, 5
	add r14, r14, r19
	invoke 5, 20, 4
	add r14, r14, r20
	invoke 5, 21, 3
	add r14, r14, r21
	set r5, r14
	invoke 5, 13, 0
	seti r12, #1
	goto_ne L2, r13, r12
L3:
	seti r11, #2
	goto_ge L7, r5, r11
L8:
	seti r10, #0
	invoke 4, 10, 0
	goto L12
L7:
	seti r9, #3
	goto_le L9, r5, r9
L10:
	seti r8, #0
	invoke 4, 8, 0
	goto L11
L9:
L11:
L12:
	goto L13
L2:
	seti r7, #3
	goto_ne L4, r5, r7
L5:
	seti r6, #1
	invoke 4, 6, 0
	goto L6
L4:
L6:
L13:
	add r1, r1, r4
	goto_lt L1, r1, r3
	add r0, r0, r4
	goto_lt L0, r0, r2
	stop
