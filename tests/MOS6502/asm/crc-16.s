CRC    = $6          ; 2 bytes in ZP
CRCLO  = $8000       ; Two 256-byte tables for quick lookup
CRCHI  = $8100       ; (should be page-aligned for speed)

  .ORG   $2000
MAKECRCTABLE:
         LDX #0          ; X counts from 0 to 255
BYTELOOP LDA #0          ; A contains the low 8 bits of the CRC-16
         STX CRC         ; and CRC contains the high 8 bits
         LDY #8          ; Y counts bits in a byte
BITLOOP  ASL
         ROL CRC         ; Shift CRC left
         BCC NOADD       ; Do nothing if no overflow
         EOR #$21        ; else add CRC-16 polynomial $1021
         PHA             ; Save low byte
         LDA CRC         ; Do high byte
         EOR #$10
         STA CRC
         PLA             ; Restore low byte
NOADD    DEY
         BNE BITLOOP     ; Do next bit
         STA CRCLO,X     ; Save CRC into table, low byte
         LDA CRC         ; then high byte
         STA CRCHI,X
         INX
         BNE BYTELOOP    ; Do next byte
         RTS

UPDCRC:
         EOR CRC+1       ; Quick CRC computation with lookup tables
         TAX
         LDA CRC
         EOR CRCHI,X
         STA CRC+1
         LDA CRCLO,X
         STA CRC
         RTS

  .ORG   $F000
CODE:
         JSR MAKECRCTABLE
         LDY #$FF
         STY CRC
         STY CRC+1
         INY
LOOP     LDA $1000,Y
         JSR UPDCRC
         INY
         BNE LOOP
EXIT     .BYTE $2         ; ReSim 6502 EXIT CODE

  .ORG   $0000
  .ORG   $FFFC
  .WORD  CODE
