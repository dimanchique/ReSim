;       ./vasmz80_oldstyle -Fbin -8080 -intel-syntax mult.s -o mult.bin

                        ; Code Segment
	    ORG	    0000h	; Set Program Counter to address 0
START:
	    MVI	    E,000h
	    LXI	    H,000h	; Clear H,L Registers to initialize Partial Product
	    MVI	    B,008h	; Iteration Count (8) to B Register
LOOP:
        DAD	    H	    ; Shift Partial Product left into Carry (H&L)
	    RAL		        ; Rotate Multiplier Bit to Carry
	    JNC	    NEXT	; Test Multiplier at Carry
	    DAD	    D	    ; Add Multiplicand to Partial Product (D&E)
	    		        ; if Carry =1
	    ACI	    000h	; (Add Carry Bit)
NEXT:
        DCR	    B	    ; Decrement Iteration Counter
    	JNZ	    LOOP	; Check Iterations
    	SHLD    TOTAL	; Store Answer in Locations 100,101
    	RET	            ; Return from subroutine

                        ; Data segment (210 = 0xD2):

	    ORG	    040h	; Set Program Counter to address 100 (octal)
TOTAL:  DS	    002h	; Reserve 2 bytes (1 word) of unintialized storage

	    END		        ; End
