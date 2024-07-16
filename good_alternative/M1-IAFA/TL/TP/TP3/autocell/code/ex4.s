@ Type exercise 4 here
	INVOKE 1, 2, 3 @ SIZE in R2 and R3
	SETI R0, #0 @ row
	SETI R4, #1
L0:
	GOTO_GE L4, R0, R3
	SETI R1, #0 @ col
L1:
	GOTO_GE L3, R1, R2
	INVOKE 3, 1, 0
	INVOKE 5, 5, 3
	GOTO_NE L2, R5, R4
	INVOKE 4, 4, 0
L2:
	ADD R1, R1, R4
	GOTO L1
L3:
	ADD R0, R0, R4
	GOTO L0
L4:
	STOP
