                    ;vasm6502_oldstyle -Fbin -dotdir mult-by-10.s -o mult-by-10.bin

MULT10  ASL         ; multiply by 2
        STA TEMP    ; temp store in TEMP
        ASL         ; again multiply by 2 (*4)
        ASL         ; again multiply by 2 (*8)
        CLC
        ADC TEMP    ; as result, A = x*8 + x*2

        RTS

TEMP    .byte 0

  .ORG  $fffc
  .WORD MULT10
