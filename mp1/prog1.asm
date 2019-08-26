;
; The code given to you here implements the histogram calculation that
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of
; code to print the histogram to the monitor.
;
; If you finish your program,
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string
; terminated by a NUL character.  Lower case and upper case should
; be counted together, and a count also kept of all non-alphabetic
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance)
; should be stored starting at x3F00, with the non-alphabetic count
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram

	; fill the histogram with zeroes
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop

;After the histogram is created, it prints the histogram, with
;the character followed by the number of occurances in hexadecimal.
;e.g.
;@ 0024
;A 000A
;B 0004
;and so on...
;
;Table of registers:
;R0 holds the temporary value that is to be printed at any time
;R1 holds the counter for number of bits that have been parsed from R3
;R2 holds the bits that have been parsed from R3
;R4 holds the counter for number of lines
;R5 holds an incremental counter for incrementing letters
;R6 holds the counter for number of letters/numbers printed on a line

PRINT_HIST
  LD R4, NUM_BINS   ;init R4 with NUM_BINS (line counter)
  AND R5, R5, #0    ;init R5
START
  LD R0, LTTR_START
  ADD R0, R0, R5    ;add R5 to R0
  OUT               ;print character
  LD R0, SPACE      ;print space
  OUT

  LD R3, HIST_ADDR  ;init R3 with location of histogram
  ADD R3, R3, R5    ;add R5 to R3
  ST R3, HIST_TEMP  ;store R3 to temp location
  LDI R3, HIST_TEMP ;load R3 from temp location
  AND R6, R6, #0
  ADD R6, R6, #4    ;init R6=4 (printed numbers counter)

LOOP_ONE
  AND R1, R1, #0
  ADD R1, R1, #4    ;init R1=4 (bit counter)
  AND R2, R2, #0    ;init R2 (bit storage)
LOOP_TWO
  ADD R3, R3, #0
  BRn NEGATIVE      ;branch if MSB=1
  BRnzp FINISH

NEGATIVE
  ADD R2, R2, #1   ;add 1 to R2

FINISH
  ADD R3, R3, R3    ;left shift R3
  ADD R1, R1, #-1   ;decrement counter
  BRz NEXT          ;branch to printing part if R1 = 0
  ADD R2, R2, R2    ;left shift R2
  ADD R1, R1, #0
  BRp LOOP_TWO      ;loop if R1>0

NEXT
  ADD R0, R2, #-9   ;check if R2<9
  BRp LTTR
  LD R0, NUMBER     ;ld R0 with ascii for '0'
  BRnzp ADDING

LTTR
  LD R0, LETTER ;ld R0 with 'A'-10
  ADDING ADD R0, R0, R2   ;load R0 with ascii character to be printed
  OUT
  ADD R6, R6, #-1   ;decrement counter
  BRp LOOP_ONE

  LD R0, NEWLINE    ;print newline
  OUT
  ADD R5, R5, #1
  ADD R4, R4, #-1   ;increment/decrement counters
  BRp START         ;loop if R4>0

DONE HALT

NEWLINE .FILL x000A ;newline char
LTTR_START .FILL x0040  ;'@'
NUMBER .FILL x0030  ;'0'
LETTER .FILL x0037  ;'A'-10
SPACE  .FILL x0020  ;' '
HIST_TEMP .BLKW #1

; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
