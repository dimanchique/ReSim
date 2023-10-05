MULT10  ASL         ;multiply by 2
        STA TEMP    ;temp store in TEMP
        ASL         ;again multiply by 2 (*4)
        ASL         ;again multiply by 2 (*8)
        CLC
        ADC TEMP    ;as result, A = x*8 + x*2
        RTS

TEMP    .byte 0