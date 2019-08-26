.ORIG x3000
; write your code here
AND R6, R6, #0
ADD R6, R6, #4    ;init R6=4 (counter)
START AND R1, R1, #0
ADD R1, R1, #4    ;init R1=4 (counter)
AND R2, R2, #0    ;init R2
LOOP ADD R3, R3, #0
BRn NEGATIVE      ;branch if MSB=1
BRnzp DONE
NEGATIVE ADD R2, R2, #1   ;add 1 to R2
DONE ADD R3, R3, R3    ;left shift R3
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
HALT
NUMBER .FILL x0030  ;ascii 0
LETTER .FILL x0037  ;ascii A-10
.END