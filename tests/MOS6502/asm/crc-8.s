CRC    = $6          	 ; 1 byte in ZP (unneeded if you inline)
CRCTBL = $8000       	 ; One 256-byte table for quick lookup

MAKECRCTABLE:
         LDX #0
BYTELOOP TXA             ; A contains the CRC-8
         LDY #8
BITLOOP  ASL             ; Shift CRC left
         BCC NOADD       ; If no overflow, do nothing
         EOR #$07        ; else add CRC-8 polynomial $07
NOADD    DEY
         BNE BITLOOP     ; Do next bit
         STA CRCTBL,X    ; All bits done, store in table
         INX
         BNE BYTELOOP    ; Do next byte
         RTS

UPDCRC:
         EOR CRC         ; You really should inline this,
         TAX             ; in which case you don't even need
         LDA CRCTBL,X    ; the CRC zero page location. See
         STA CRC         ; example below.
         RTS

CODE:
         JSR MAKECRCTABLE
         LDY #0
         TYA             ; Initialize CRC
LOOP     EOR $1000,Y     ; EOR old CRC with data
         TAX             ; and index into table
         LDA CRCTBL,X    ; to get the new CRC
         INY
         BNE LOOP
EXIT     .BYTE $2	     ; ReSim 6502 EXIT CODE

  .ORG   $FFFC
  .WORD  CODE
