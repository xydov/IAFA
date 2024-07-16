@ Type exercise 1 here	
	SETI R0, #0
	SETI R1, #1
	SETI R2, #2
L1:
	GOTO_GE L2, R0, R2
	ADD R0, R0, R1
	GOTO L1
L2:
	STOP

