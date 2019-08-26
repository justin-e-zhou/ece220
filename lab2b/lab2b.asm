;number to print in decimal is in R3.
;it will be positive.
.ORIG x3000
LD R6, ASCII_0
MAIN_LOOP
AND R4, R4, #0
ADD R4, R4, #10
JSR DIV
AND R3, R3, #0
ADD R3, R3, R0
AND R0, R0, #0
ADD R0, R0, R1
JSR PUSH
ADD R3, R3, #0
BRp MAIN_LOOP
POP_LOOP
JSR POP
ADD R5, R5, #0
BRp DONE
ADD R0, R6, R0
OUT
BRnzp POP_LOOP

DONE
HALT

ASCII_0 .FILL x30
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0-quotient, R1-remainder
DIV
AND R0, R0, #0
AND R1, R1, #0
ADD R1, R1, R3
NOT R4, R4
ADD R4, R4, #1

DIV_LOOP
  ADD R1, R1, R4
  BRn DIV_NEG
  ADD R0, R0, #1
  ADD R1, R1, #0
  BRz DIV_DONE
  BRnzp DIV_LOOP
DIV_NEG
  NOT R4, R4
  ADD R4, R4, #1
  ADD R1, R4, R1
DIV_DONE
RET


;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

.END

