; minimal monitor for EhBASIC and 6502 simulator V1.05
; Modified for ReSim with segments and D010-D012 I/O

; =============================================================================
; SEGMENT: CODE - BASIC code at $C000
; =============================================================================
.segment "CODE"

; External symbols that basic.asm references
IRQ_vec = $FFB0
NMI_vec = $FFBA

.include "basic.asm"

; =============================================================================
; SEGMENT: MONITOR - Monitor code at $FF80
; =============================================================================
.segment "MONITOR"
.org $FF80

; reset vector points here
RES_vec
        CLD                     ; clear decimal mode
        LDX   #$FF              ; empty stack
        TXS                     ; set the stack

; set up vectors and interrupt code, copy them to page 2

        LDY   #END_CODE-LAB_vec ; set index/count
LAB_stlp
        LDA   LAB_vec-1,Y       ; get byte from interrupt code
        STA   VEC_IN-1,Y        ; save to RAM
        DEY                     ; decrement index/count
        BNE   LAB_stlp          ; loop if more to do

; now do the signon message, Y = $00 here

LAB_signon
        LDA   LAB_mess,Y        ; get byte from sign on message
        BEQ   LAB_nokey         ; exit loop if done

        JSR   V_OUTP            ; output character
        INY                     ; increment index
        BNE   LAB_signon        ; loop, branch always

LAB_nokey
        JSR   V_INPT            ; call scan input device
        BCC   LAB_nokey         ; loop if no key

        AND   #$DF              ; mask xx0x xxxx, ensure upper case
        CMP   #'W'              ; compare with [W]arm start
        BEQ   LAB_dowarm        ; branch if [W]arm start

        CMP   #'C'              ; compare with [C]old start
        BNE   RES_vec           ; loop if not [C]old start

        JMP   LAB_COLD          ; do EhBASIC cold start

LAB_dowarm
        JMP   LAB_WARM          ; do EhBASIC warm start

; byte out to ReSim TTY (D012)

ACIAout
        STA   $D012            ; write to TTY output register
        RTS

; byte in from ReSim keyboard (D010)

ACIAin
        LDA   $D010            ; get keyboard status/data
        BEQ   LAB_nobyw         ; branch if no byte waiting

        AND   #$7F              ; clear high bit
        SEC                     ; flag byte received
        RTS

LAB_nobyw
        CLC                     ; flag no byte received
no_load                       ; empty load vector for EhBASIC
no_save                       ; empty save vector for EhBASIC
        RTS

; vector tables

LAB_vec
        .word ACIAin            ; byte in from keyboard
        .word ACIAout           ; byte out to TTY
        .word no_load           ; null load vector for EhBASIC
        .word no_save           ; null save vector for EhBASIC

; EhBASIC IRQ support

IRQ_CODE
        PHA                     ; save A
        LDA   IrqBase           ; get the IRQ flag byte
        LSR                     ; shift the set b7 to b6, and on down ...
        ORA   IrqBase           ; OR the original back in
        STA   IrqBase           ; save the new IRQ flag byte
        PLA                     ; restore A
        RTI

; EhBASIC NMI support

NMI_CODE
        PHA                     ; save A
        LDA   NmiBase           ; get the NMI flag byte
        LSR                     ; shift the set b7 to b6, and on down ...
        ORA   NmiBase           ; OR the original back in
        STA   NmiBase           ; save the new NMI flag byte
        PLA                     ; restore A
        RTI

END_CODE

LAB_mess
        .byte $0D,$0A,"6502 EhBASIC [C]old/[W]arm ?",$00

; =============================================================================
; SEGMENT: VECTORS - 6502 vectors at $FFFA
; =============================================================================
.segment "VECTORS"
.org $FFFA

        .word NMI_CODE          ; NMI vector -> points to NMI handler code
        .word RES_vec           ; RESET vector -> $FF80
        .word IRQ_CODE          ; IRQ vector -> points to IRQ handler code

        .end RES_vec            ; set start at reset vector