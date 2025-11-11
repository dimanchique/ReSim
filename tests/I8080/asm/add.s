;       ./vasmz80_oldstyle -Fbin -8080 -intel-syntax add.s -o add.bin

                    ; Code Segment
	    ORG	0o	    ; Set Program Counter to address 0
START:	LDA	VAL1	; Load value (5) at VAL1 (200) into Accumulator
	    MOV	B,A	    ; Move value in Accumulator to Register B
	    LDA	VAL2	; Load value (8) at VAL2 (201) into Accumulator
	    ADD	B	    ; Add value in Register B to value in Accumulator
	    STA	SUM	    ; Store accumulator at SUM (202)
	    RET	        ; Return from subroutine

                    ; Data segment:

	    ORG	200o	; Set Program Counter to address 200
VAL1:	DB	5o	    ; Data Byte at address 200 = 5
VAL2:	DB	10o	    ; Data Byte at address 201 = 8 (10 octal)
SUM:	DB	0o	    ; Data Byte at address 202 = 0

	    END		; End
