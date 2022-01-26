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
;
;Partners: mswei2, bmaedge2
;
; The code below is written so that it will print out a hexidecimal number representing
; how many occurrances a letter has shown. @ will represent non-alphabet values and A-Z
; will represent themselves. This code is the rest of the histogram code.
;
; When deciding how to write the code, I decided to check only the 15th bit of the value at one time.
; From there, I continuously left-shifted the value until all 16 bits had been checked.
; Since the printed value is in the form 0000, each 0 is separated into 4 bits. I created a
; temporary container to hold these 4 bits at a time and converted them to there hexadecimal value
; (0,1,2,3,4,5,6,7,8,9,A,B,C,D,F) where they would then get printed. I also utilized loops and counters
; to make sure only @ and A-Z were printed and only 4 bits were getting printed. Counters were also used
; to ensure 16 bits were checked. For printing, I stored repeated values in memory for easier recalling
; and also used additional memory to act as a register of sorts with LD and ST. For checking the bit,
; I ANDed the value with x8000 making sure only the 15th bit was checked and if it was 0, then I
; would have it print 0 and 1 if it was negative or positive. When printing, values could be a decimal
; or a number, so I also had to implement a method to determine if it was 0-9 or A-F.
;
; Table of registers used in this part of the code:
;
;    R0 acts as the printing register
;    R1 holds the value x8000 used for checking the value of the 15th bit
;    R2 holds the value being checked by x8000
;    R3 acts as a register to hold the value after the checked value is ANDed with x8000
;    R4 holds the bit counter to make sure no more than 4 bits are converted at a time
;    R5 holds the histogram address
;    R6 is used as a temporary register
;
;    Matthew Shuyu Wei
;    mswei2
;    January 25, 2022

PRINT_HIST			;Start of printing
	LD  R5,HIST_ADDR	;Loads histogram address to address register
	LD  R1,CHECK		;Loaders x8000 to checking register
	ADD R5,R5,#-1		;Subtracts 1 from address register

START				;Initializes everything for the line being printed
	LD  R0,ASCII		;Loads current value being printed to printing register
	OUT			;Prints from printing register
	ADD R0,R0,#1		;Sets next ASCII value being printed
	ST  R0,ASCII		;Stores ASCII back to memory
	LD  R0,SPACE		;Loads ASCII value for space to printing register
	OUT			;Prints from printing register
	ADD R5,R5,#1		;Add one to the histogram address
	LDR R2,R5,#0		;Load value from histogram address to register 2
	AND R4,R4,#0		;Reset counter to 0
	ADD R4,R4,#4		;Set counter to 4
	LD  R6,COUNT		;Load counter to temporary register
	AND R6,R6,#0		;Resets counter for future loops
	ADD R6,R6,#4		;Sets counter to 4
	ST  R6,COUNT		;Stores coutner back to memory

VALUE_CHECKER			;Determines if value is 0 or 1
	AND R3,R1,R2		;ANDs value and x8000 to determine if value if 1 or 0
	BRz ZERO		;Branch to ZERO if 0
	BRnp ONE		;Branch to ONE if 1

ONE				;Adds one to temporary 4-bit container
	LD  R6,ASCII_COUNT	;Loads 4-bit container to temporary register
	ADD R6,R6,R6		;Left-Shifts 4-bit container
	ADD R2,R2,R2		;Left-Shifts histogram value
	ADD R6,R6,#1		;Adds one to 4-bit container
	ST  R6,ASCII_COUNT	;Stores 4-bit container back to memory
	ADD R4,R4,#-1		;Decrement counter
	BRz DET_VAL		;Branch to DET_VAL if 4 bits have been checked
	BRnp VALUE_CHECKER	;Branch to VALUE_CHECKER for next bit

ZERO				;Adds zero to temporary 4-bit container
	LD  R6,ASCII_COUNT	;Loads 4-bit container to temporary register
	ADD R6,R6,R6		;Left-Shifts 4-bit container
	ADD R2,R2,R2		;Left-Shifts histogram value
	ST  R6,ASCII_COUNT	;Stores 4-bit container back to memory
	ADD R4,R4,#-1		;Decrement counter
	BRz DET_VAL		;Branch to DET_VAL if 4 bits have been checked
	BRnp VALUE_CHECKER	;Branch to VALUE_CHECKER for next bit

DET_VAL				;Determines if the group of 4 bits is 0-9 or A-F
	LD  R6,ASCII_COUNT	;Loads 4-bit container to temporary register
	ADD R6,R6,#-9		;Subtracts 9 from register to determine if value should be 0-9 or A-F
	BRp PRINT_ALPHA		;Branch to PRINT_ALPHA if value is greater than 9
	BRnz PRINT_NUM		;Branch to PRINT_NUM if value is less than or equal to 9

PRINT_NUM			;Prints number 0-9
	LD R0,ASCII_COUNT	;Loads number into printing register
	LD R6,NUM		;Loads ASCII value for 0 to temporary register
	ADD R0,R0,R6		;Sets printing register equal to number for printing
	OUT			;Prints from printing register
	LD  R6,ASCII_COUNT	;Loads ASCII_COUNT to temporary register
	AND R6,R6,#0		;Resets ASCII_COUNT to 0
	ST  R6,ASCII_COUNT	;Stores ASCII_COUNT back to memory
	LD  R6,COUNT		;Loads counter to temporary register
	ADD R6,R6,#-1		;Decrements from coutner
	BRz FINISH		;Goes to FINISH if counter reaches 0
	ST  R6,COUNT		;Stores counter back to memory
	ADD R4,R4,#4		;Resets bit counter back to 4
	BRnzp VALUE_CHECKER	;Branches to VALUE_CHECKER

PRINT_ALPHA			;Prints letter A-F
	LD R0,HEX		;Loads @ into register
	ADD R0,R0,R6		;Adds offest to get R0 equal to A-F
	OUT			;Prints from printing register
	LD  R6,ASCII_COUNT	;Loads ASCII_COUNT to temporary register
	AND R6,R6,#0		;Resets ASCII_COUNT to 0
	ST  R6,ASCII_COUNT	;Stores ASCII_COUNT back to memory
	LD  R6,COUNT		;Loads coutner to temporary register
	ADD R6,R6,#-1		;Subtracts 1 from coutner
	BRz FINISH		;Goes to FINISH if counter reaches 0
	ST  R6,COUNT		;Stores counter back to memory
	ADD R4,R4,#4		;Resets bit counter back to 4
	BRnzp VALUE_CHECKER	;Branches to VALUE_CHECKER

FINISH				;Done printing current line, prints new line and resets memory
	LD  R6,ASCII_COUNT	;Loads ASCII_COUNT to temporary register
	AND R6,R6,#0		;Resets ASCII_COUNT to 0
	ST  R6,ASCII_COUNT	;Stores ASCII_COUNT back to memory
	LD  R0,NEW_LINE		;Loads ASCII value for a new line to printing register
	OUT			;Prints from printing register
	LD  R6,LETTER_COUNT	;Loads LETTER_COUNT to temporary register
	ADD R6,R6,#-1		;Decrement counter
	BRz DONE		;Ends program if counter reaches 0
	ST  R6,LETTER_COUNT	;Stores LETTER_COUNT back to memory
	BRnzp START		;Branches to START
	

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments
	




DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'

ASCII		.FILL x0040	;ASCII value of @
SPACE		.FILL x0020	;ASCII value of space
HEX		.FILL x0040 	;Start of alphabet counter
NUM		.FILL x0030	;ASCII value of 0
NEW_LINE	.FILL x000A	;ASCII value of 0 New Line
CHECK		.FILL x8000	;Holds 1000000000000000 so it can be used to check the 15th bit
COUNT		.FILL x0000	;Acts as a counter to make sure only 4 digits are printed
ASCII_COUNT	.FILL x0000	;Acts as a container to hold the 4 digits being printed
LETTER_COUNT	.FILL #27	;Acts as a counter to make sure only 27 lines are printed

HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address



; for testing, you can use the lines below to include the string in this
; program...

; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
