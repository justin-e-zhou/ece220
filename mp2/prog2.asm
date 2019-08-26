;This code is a stack calculator, calculating expressions using the postfix
;expression. (i.e. (3-4)*5+(5-2)=-2 --> 34-5*52-+=-2)
;The code can take in numbers or operators (+,-,*,/,^) and will error out
;when an invalid character is input. The program will output the answer
;once an '=' is typed, if and only if the answer is the only item in the
;stack. The answer will be output in hexadecimal (i.e. x0010, x00F1, etc.).
;The program will ignore spaces anywhere in the expression.

.ORIG x3000
;your code goes here
INPUT
GETC
OUT

LD R1, NEG_SPACE  ;loop if input is ' '
ADD R1, R0, R1
BRz INPUT

LD R1, NEG_EQUALS ;check if input is '='
ADD R1, R0, R1
BRz EVALUATE

LD R1, NEG_POW  ;check if input is '^'
ADD R1, R0, R1
BRz EVALUATE

LD R1, NEG_MULT ;check if input is '*'
ADD R1, R0, R1
BRz EVALUATE
BRn INVALID     ;if input is less than '*', it is invalid
ADD R1, R1, #-1 ;check if input is '+'
BRz EVALUATE
ADD R1, R1, #-2 ;check if input is '-'
BRz EVALUATE
ADD R1, R1, #-2 ;check if input is '/'
BRz EVALUATE
ADD R1, R1, #-11;check if input is between '0' and '9'
BRzp INVALID    ;if greater than '9', input is invalid
ADD R0, R1, #10 ;if it is, store to R0 and push
JSR PUSH
BRnzp INPUT

DONE HALT

NEG_SPACE .FILL xFFE0
NEG_EQUALS .FILL xFFC3
NEG_MULT .FILL xFFD6
NEG_POW .FILL xFFA2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
ST R5, HEX_SAVER5
LD R0, HEX_X
OUT
AND R0, R0, #0
AND R6, R6, #0
ADD R6, R6, #4    ;init R6=4 (counter)
START AND R1, R1, #0
ADD R1, R1, #4    ;init R1=4 (counter)
AND R2, R2, #0    ;init R2
LOOP ADD R3, R3, #0
BRn NEGATIVE      ;branch if MSB=1
BRnzp HEX_DONE
NEGATIVE
ADD R2, R2, #1   ;add 1 to R2
HEX_DONE
ADD R3, R3, R3    ;left shift R3
ADD R1, R1, #-1   ;decrement counter
BRz NEXT          ;branch to printing part if counter = 0
ADD R2, R2, R2    ;left shift R2
ADD R1, R1, #0
BRp LOOP          ;loop if R1>0
NEXT ADD R4, R2, #-9   ;check if R2<9
BRp LTTR
LD R5, NUMBER     ;ld R5 with ascii for 0
BRnzp ADDING
LTTR LD R5, LETTER ;ld R5 with ascii for A-10
ADDING ADD R0, R2, R5   ;load R0 with ascii character to be printed
OUT
ADD R6, R6, #-1   ;decrement counter
BRp START
LD R5, HEX_SAVER5
HALT

HEX_SAVER5 .BLKW #1
HEX_X .FILL x0078 ;'x'
NUMBER .FILL x0030  ;ascii 0
LETTER .FILL x0037  ;ascii A-10
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
EVALUATE
LD R1, NEG_POW  ;check if input is '^'
ADD R1, R0, R1
BRnp NOT_EXP
JSR EXP

NOT_EXP
LD R1, NEG_MULT ;check if input is '*'
ADD R1, R0, R1
BRnp NOT_MUL
JSR MUL

NOT_MUL
ADD R1, R1, #-1 ;check if input is '+'
BRnp NOT_PLUS
JSR PLUS

NOT_PLUS
ADD R1, R1, #-2 ;check if input is '-'
BRnp NOT_MIN
JSR MIN

NOT_MIN
ADD R1, R1, #-2 ;check if input is '/'
BRnp NOT_DIV
JSR DIV

NOT_DIV
LD R1, NEG_EQUALS ;check if input is '='
ADD R1, R1, R0
BRnp NOT_EQUALS
JSR POP
ADD R5, R5, #0
BRp INVALID       ;invalid if stack underflows or if there are items in stack
LD R4, STACK_TOP  ;(if stack start - stack top != 0)
LD R5, STACK_START
NOT R4, R4
ADD R4, R4, #1
ADD R4, R5, R4
BRnp INVALID
AND R3, R3, #0    ;if valid, print R3<-R0, print hex
AND R5, R5, #0
ADD R5, R5, R0
ADD R3, R3, R0
JSR PRINT_HEX

NOT_EQUALS
ADD R5, R5, #0  ;check if any of the subroutines errored out
BRp INVALID
BRnzp INPUT

;your code goes here
INVALID
LEA R0, INVALID_STRING
PUTS
HALT
INVALID_STRING .STRINGZ "Invalid Expression"


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;pops the top two values from stack, evaluates them,
;and pushes the answer back on the stack
;output R5 (0 - success, 1 - fail)
PLUS
;your code goes here
;save registers
ST R0, PLUS_SAVER0
ST R3, PLUS_SAVER3
ST R4, PLUS_SAVER4
ST R6, PLUS_SAVER6
ST R7, PLUS_SAVER7
;load stack top pointer
LD R6, STACK_TOP
;first pop
JSR POP
AND R3, R3, #0
ADD R3, R3, R0
;check return value, ERROR if failed
ADD R5, R5, #0
BRp PLUS_ERROR
;second pop
JSR POP
AND R4, R4, #0
ADD R4, R4, R0
;check result, go to RESTORE if failed
ADD R5, R5, #0
BRp PLUS_RESTORE
;add R3+R4
ADD R0, R3, R4
;push result to stack
JSR PUSH
AND R5, R5, #0
BRnzp PLUS_EXIT
PLUS_RESTORE
;put back first number
ST R6, STACK_TOP
PLUS_ERROR
AND R5, R5, #0
ADD R5, R5, #1
PLUS_EXIT
;restore registers
LD R0, PLUS_SAVER0
LD R3, PLUS_SAVER3
LD R4, PLUS_SAVER4
LD R6, PLUS_SAVER6
LD R7, PLUS_SAVER7
RET

PLUS_SAVER0 .BLKW #1
PLUS_SAVER3 .BLKW #1
PLUS_SAVER4 .BLKW #1
PLUS_SAVER6 .BLKW #1
PLUS_SAVER7 .BLKW #1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;pops the top two values from stack, evaluates them,
;and pushes the answer back on the stack
;output R5 (0 - success, 1 - fail)
MIN
;your code goes here
;save registers
ST R0, MIN_SAVER0
ST R3, MIN_SAVER3
ST R4, MIN_SAVER4
ST R6, MIN_SAVER6
ST R7, MIN_SAVER7
;load stack top pointer
LD R6, STACK_TOP
;first pop
JSR POP
AND R3, R3, #0
ADD R3, R3, R0
;check return value, ERROR if failed
ADD R5, R5, #0
BRp MIN_ERROR
;second pop
JSR POP
AND R4, R4, #0
ADD R4, R4, R0
;check result, go to RESTORE if failed
ADD R5, R5, #0
BRp MIN_RESTORE
;subtract R4-R3
NOT R3, R3
ADD R3, R3, #1
ADD R0, R3, R4
;push result to stack
JSR PUSH
AND R5, R5, #0
BRnzp MIN_EXIT
MIN_RESTORE
;put back first number
ST R6, STACK_TOP
MIN_ERROR
AND R5, R5, #0
ADD R5, R5, #1
MIN_EXIT
;restore registers
LD R0, MIN_SAVER0
LD R3, MIN_SAVER3
LD R4, MIN_SAVER4
LD R6, MIN_SAVER6
LD R7, MIN_SAVER7
RET

MIN_SAVER0 .BLKW #1
MIN_SAVER3 .BLKW #1
MIN_SAVER4 .BLKW #1
MIN_SAVER6 .BLKW #1
MIN_SAVER7 .BLKW #1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;pops the top two values from stack, evaluates them,
;and pushes the answer back on the stack
;output R0, R5 (0 - success, 1 - fail)
MUL
;your code goes here
;save registers
ST R0, MUL_SAVER0
ST R3, MUL_SAVER3
ST R4, MUL_SAVER4
ST R6, MUL_SAVER6
ST R7, MUL_SAVER7
;load stack top pointer
LD R6, STACK_TOP
;first pop
JSR POP
AND R3, R3, #0
ADD R3, R3, R0
;check return value, ERROR if failed
ADD R5, R5, #0
BRp MUL_ERROR
;second pop
JSR POP
AND R4, R4, #0
ADD R4, R4, R0
;check result, go to RESTORE if failed
ADD R5, R5, #0
BRp MUL_RESTORE
;multiply R3*R4
AND R0, R0, #0
ADD R3, R3, #0  ;check if R3 is negative
BRzp MUL_LOOP
NOT R3, R3
ADD R3, R3, #1  ;negate R3
NOT R4, R4
ADD R4, R4, #1  ;negate R4
MUL_LOOP
ADD R3, R3, #0
BRz MUL_DONE
ADD R0, R0, R4
ADD R3, R3, #-1
BRnzp MUL_LOOP
MUL_DONE
;push result to stack
JSR PUSH
AND R5, R5, #0
BRnzp MUL_EXIT
MUL_RESTORE
;put back first number
ST R6, STACK_TOP
MUL_ERROR
AND R5, R5, #0
ADD R5, R5, #1
MUL_EXIT
;restore registers
LD R0, MUL_SAVER0
LD R3, MUL_SAVER3
LD R4, MUL_SAVER4
LD R6, MUL_SAVER6
LD R7, MUL_SAVER7
RET

MUL_SAVER0 .BLKW #1
MUL_SAVER3 .BLKW #1
MUL_SAVER4 .BLKW #1
MUL_SAVER6 .BLKW #1
MUL_SAVER7 .BLKW #1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;pops the top two values from stack, evaluates them,
;and pushes the answer back on the stack
;output R0, R5 (0 - success, 1 - fail)
DIV
;your code goes here
;save registers
ST R0, DIV_SAVER0
ST R2, DIV_SAVER2
ST R3, DIV_SAVER3
ST R4, DIV_SAVER4
ST R6, DIV_SAVER6
ST R7, DIV_SAVER7
;load stack top pointer
LD R6, STACK_TOP
;first pop
JSR POP
AND R3, R3, #0
ADD R3, R3, R0
;check return value, ERROR if failed
ADD R5, R5, #0
BRp DIV_ERROR
;second pop
JSR POP
AND R4, R4, #0
ADD R4, R4, R0
;check result, go to RESTORE if failed
ADD R5, R5, #0
BRp DIV_RESTORE
;divide R4/R3
AND R0, R0, #0  ;clear R0
AND R2, R2, #0
ADD R2, R2, #-1 ;set indicator register
ADD R3, R3, #0
BRn DIV_R4NEG   ;negate R3 if positive
NOT R3, R3
ADD R3, R3, #1
BRz DIV_RESTORE ;error out of zero
BRnzp DIV_R4NEG2
DIV_R4NEG
ADD R2, R2, #1  ;indicate if R3 is negative
DIV_R4NEG2
ADD R4, R4, #0
BRzp DIV_LOOP   ;negate R4 if negative
NOT R4, R4
ADD R4, R4, #1
ADD R2, R2, #1  ;indicate if R4 is negative
DIV_LOOP
ADD R4, R4, R3
BRn DIV_DONE    ;exit loop if negative
ADD R0, R0, #1
ADD R4, R4, #0
BRp DIV_LOOP    ;loop if R4 positive
DIV_DONE
ADD R2, R2, #0  ;if R2=0, negate answer
BRnp DIV_PUSH
NOT R0, R0
ADD R0, R0, #1
;push result to stack
DIV_PUSH
JSR PUSH
AND R5, R5, #0
BRnzp DIV_EXIT
DIV_RESTORE
;put back first number
ST R6, STACK_TOP
DIV_ERROR
AND R5, R5, #0
ADD R5, R5, #1
DIV_EXIT
;restore registers
LD R0, DIV_SAVER0
LD R2, DIV_SAVER2
LD R3, DIV_SAVER3
LD R4, DIV_SAVER4
LD R6, DIV_SAVER6
LD R7, DIV_SAVER7
RET

DIV_SAVER0 .BLKW #1
DIV_SAVER2 .BLKW #1
DIV_SAVER3 .BLKW #1
DIV_SAVER4 .BLKW #1
DIV_SAVER6 .BLKW #1
DIV_SAVER7 .BLKW #1


STACK_START	.FILL x4000	;put here so it is not out of range
STACK_TOP	.FILL x4000	;of LD function earlier in code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;pops the top two values from stack, evaluates them,
;and pushes the answer back on the stack
;output R0, R5 (0 - success, 1 - fail)
EXP
;your code goes here
;save registers
ST R0, EXP_SAVER0
ST R2, EXP_SAVER2
ST R3, EXP_SAVER3
ST R4, EXP_SAVER4
ST R6, EXP_SAVER6
ST R7, EXP_SAVER7
;load stack top pointer
LD R6, STACK_TOP
;first pop
JSR POP
AND R3, R3, #0
ADD R3, R3, R0
;check return value, ERROR if failed
ADD R5, R5, #0
BRp EXP_ERROR
;second pop
JSR POP
AND R4, R4, #0
ADD R4, R4, R0
;check result, go to RESTORE if failed
ADD R5, R5, #0
BRp EXP_RESTORE
;perform R4^R3
AND R0, R0, #0
ADD R0, R0, #1  ;R0=1 for case x^0
AND R2, R2, #0
ADD R2, R2, R4
ADD R3, R3, #0
BRz EXP_DONE    ;check R3=0
AND R0, R0, #0
ADD R0, R0, R4  ;R0=R4 for case x^1
ADD R3, R3, #-1
BRnz EXP_DONE   ;check R3=1
EXP_LOOP
AND R0, R0, #0
ADD R0, R0, R4
JSR PUSH
AND R0, R0, #0
ADD R0, R0, R2  ;R2 = answer
JSR PUSH        ;push R4 and R2
JSR MUL         ;multiply R4 and R2
JSR POP
AND R2, R2, #0
ADD R2, R2, R0
ADD R3, R3, #-1
BRp EXP_LOOP
EXP_DONE
;push result to stack
JSR PUSH
AND R5, R5, #0
BRnzp EXP_EXIT
EXP_RESTORE
;put back first number
ST R6, STACK_TOP
EXP_ERROR
AND R5, R5, #0
ADD R5, R5, #1
EXP_EXIT
;restore registers
LD R0, EXP_SAVER0
LD R2, EXP_SAVER2
LD R3, EXP_SAVER3
LD R4, EXP_SAVER4
LD R6, EXP_SAVER6
LD R7, EXP_SAVER7
RET

EXP_SAVER0 .BLKW #1
EXP_SAVER2 .BLKW #1
EXP_SAVER3 .BLKW #1
EXP_SAVER4 .BLKW #1
EXP_SAVER6 .BLKW #1
EXP_SAVER7 .BLKW #1

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

.END
