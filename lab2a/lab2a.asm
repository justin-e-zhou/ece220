.ORIG x3000
; Write code to read in characters and echo them
; till a newline character is entered.
INPUT
  GETC
  LD R1, NEG_SPACE
  ADD R1, R0, R1
  BRz INPUT

  LD R1, NEG_NEW_LINE
  ADD R1, R0, R1
  BRz DONE

  LD R1, NEG_CHAR_RETURN
  ADD R1, R0, R1
  BRz DONE

  OUT
  JSR IS_BALANCED
  BRnzp INPUT

  DONE HALT

SPACE   .FILL x0020
NEG_SPACE .FILL xFFEF
NEW_LINE        .FILL x000A
NEG_NEW_LINE    .FILL xFFF6
CHAR_RETURN     .FILL x000D
NEG_CHAR_RETURN .FILL xFFF3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack
;if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else 1.
IS_BALANCED
  LD R1, NEG_OPEN
  ST R7, BALANCE_SAVE_R7

  ADD R1, R0, R1
  BRnp NOT_PUSH
  JSR PUSH
NOT_PUSH
  ADD R1, R1, #-1
  BRnp NOT_POP
  JSR POP
NOT_POP
  ADD R5, R5, #0
  BRz BALANCE
  ADD R5, R5, #-3
BALANCE
  ADD R5, R5, #1
  BRn DONE

  LD R7, BALANCE_SAVE_R7
  RET

NEG_OPEN .FILL xFFD8
BALANCE_SAVE_R7  .BLKW #1
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
  ST R3, PUSH_SaveR3      ;save R3
  ST R4, PUSH_SaveR4      ;save R4
  AND R5, R5, #0          ;
  LD R3, STACK_END        ;
  LD R4, STACK_TOP        ;
  ADD R3, R3, #-1         ;
  NOT R3, R3              ;
  ADD R3, R3, #1          ;
  ADD R3, R3, R4          ;
  BRz OVERFLOW            ;stack is full
  STR R0, R4, #0          ;no overflow, store value in the stack
  ADD R4, R4, #-1         ;move top of the stack
  ST R4, STACK_TOP        ;store top of stack pointer
  BRnzp DONE_PUSH         ;
OVERFLOW
  ADD R5, R5, #1          ;
DONE_PUSH
  LD R3, PUSH_SaveR3      ;
  LD R4, PUSH_SaveR4      ;
  RET


PUSH_SaveR3     .BLKW #1        ;
PUSH_SaveR4     .BLKW #1        ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
  ST R3, POP_SaveR3       ;save R3
  ST R4, POP_SaveR4       ;save R3
  AND R5, R5, #0          ;clear R5
  LD R3, STACK_START      ;
  LD R4, STACK_TOP        ;
  NOT R3, R3              ;
  ADD R3, R3, #1          ;
  ADD R3, R3, R4          ;
  BRz UNDERFLOW           ;
  ADD R4, R4, #1          ;
  LDR R0, R4, #0          ;
  ST R4, STACK_TOP        ;
  BRnzp DONE_POP          ;
UNDERFLOW
  ADD R5, R5, #1          ;
DONE_POP
  LD R3, POP_SaveR3       ;
  LD R4, POP_SaveR4       ;
  RET


POP_SaveR3      .BLKW #1        ;
POP_SaveR4      .BLKW #1        ;
STACK_END       .FILL x3FF0     ;
STACK_START     .FILL x4000     ;
STACK_TOP       .FILL x4000     ;

.END

