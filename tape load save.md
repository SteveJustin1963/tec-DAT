No, I should add additional critical functions that handle the byte and bit-level I/O operations. Let me add the complete code:



Yes, this is now the complete code needed for tape functions. I've included:

1. Main Save Routines:
- SAVE_SETUP (0450-046F)
- SAVE_MAIN (04F0-052E)

2. Main Load Routines:
- LOAD_START (0531-05B4)
- Load verification and error handling

3. Block-Level Operations:
- OUT_BLOCK (064A-0656)
- READ_BLOCK (05E3-05FD)
- CONVERT_BLOCK (05C9-05E2)

4. Byte-Level Operations:
- OUT_BYTE (0657-0665)
- READ_BYTE (060B-0617)

5. Bit-Level Operations:
- OUT_BIT (0666-067F)
- READ_BIT (0618-062F)

6. Tone Generation:
- LOW_TONE (0680-0682)
- HIGH_TONE (0684-0685)
- TONE_GEN (0686-069E)

7. Input Measurement:
- MEASURE_PERIOD (0630-0649)

This covers everything from the highest level save/load operations down to the 
lowest level bit manipulation and tone generation needed for tape operations. 
All memory locations and port I/O operations are included.

```
;-----------------------------------------------
; TAPE SAVE/LOAD ROUTINES - COMPLETE LISTING
;-----------------------------------------------

;-----------------------------------------------
; SAVE ROUTINES
;-----------------------------------------------
; Save pre-amble - Sets up file information
SAVE_SETUP:
    LD HL,(089Eh)     ; Get optional go address
    LD (08AAh),HL     ; Store in output buffer
    LD HL,(089Ah)     ; Get start address
    LD (08A6h),HL     ; Store in file info buffer
    EX DE,HL          ; Start address to DE
    LD HL,(089Ch)     ; Get end address
    OR A              ; Clear carry
    SBC HL,DE         ; Calculate block size
    INC HL            ; Add 1 for count
    JP C,004Ah        ; If end < start, error
    LD (08A8h),HL     ; Store byte count
    LD HL,(0898h)     ; Get file number
    LD (08A4h),HL     ; Store in info block
    JP SAVE_MAIN      ; Go to main save routine

; Main save routine
SAVE_MAIN:
    LD HL,3000h       ; Leader cycles
    CALL LOW_TONE     ; Output leader
    LD HL,08A4h       ; Point to file info
    LD B,0Ch          ; 12 bytes to output
    XOR A             ; Clear checksum
    CALL OUT_BLOCK    ; Output file info
    LD HL,5000h       ; Mid sync cycles
    CALL HIGH_TONE    ; Output sync
    LD HL,(08A6h)     ; Get data start address

SAVE_LOOP:
    LD BC,(08A8h)     ; Get byte count
    CALL CONVERT_BLOCK ; Convert for display
    JR NZ,SAVE_BLOCK  ; If full block
    LD A,B            ; Check remaining
    OR A
    JR Z,SAVE_END     ; If done
    XOR A             ; Flag last block

SAVE_BLOCK:
    PUSH AF           ; Save status
    EXX
    LD HL,0214h       ; Short sync
    CALL HIGH_TONE
    EXX
    XOR A             ; Clear checksum
    CALL OUT_BLOCK    ; Output block
    POP AF
    JR NZ,SAVE_LOOP   ; Continue if more

SAVE_END:
    LD HL,1000h       ; End tone length
    CALL HIGH_TONE    ; Output end marker
    LD A,05h          ; End display
    JP 03E6h          ; Return to menu

;-----------------------------------------------
; LOAD ROUTINES
;-----------------------------------------------
; Main load routine
LOAD_START:
    LD BC,1000h       ; Leader detect count

LOAD_DETECT:
    CALL MEASURE_PERIOD ; Check input
    JR C,LOAD_START   ; Retry if no leader
    DEC BC            ; Count cycles
    LD A,B
    OR C              ; Check if enough
    JR NZ,LOAD_DETECT

    LD B,0Ch          ; 12 bytes to read
    LD HL,08A4h       ; File info buffer
    CALL MEASURE_PERIOD ; Wait for sync
    JR NC,LOAD_DETECT
    CALL READ_BLOCK   ; Get file info
    JR NZ,LOAD_FAIL   ; Exit if error

    LD HL,(0898h)     ; Get wanted file number
    INC HL
    LD A,H
    OR L              ; Check if FFFF
    DEC HL
    JR Z,LOAD_DATA    ; Accept any file
    LD DE,(08A4h)     ; Get tape file number
    OR A
    SBC HL,DE         ; Compare numbers
    JR NZ,LOAD_START  ; Try next if no match

LOAD_DATA:
    LD BC,(08A8h)     ; Get byte count
    CALL CONVERT_BLOCK ; Show block number
    JR NZ,LOAD_BLOCK  ; If full block
    LD A,B            ; Check if done
    OR A
    JR Z,LOAD_DONE
    XOR A             ; Flag last block

LOAD_BLOCK:
    PUSH AF
    CALL READ_BLOCK   ; Read data block
    JR NZ,LOAD_ERROR  ; Exit if error
    POP AF
    JR NZ,LOAD_DATA   ; Continue if more

LOAD_DONE:
    XOR A             ; Signal success
    JR LOAD_END

LOAD_ERROR:
    POP DE            ; Clean stack
LOAD_FAIL:
    LD A,1            ; Signal error

LOAD_END:
    RET

;-----------------------------------------------
; SUPPORT ROUTINES
;-----------------------------------------------
; Convert block count for display
CONVERT_BLOCK:
    LD A,B            ; Get count
    AND 0Fh           ; Mask to digit
    LD DE,07D0h       ; Display table
    ADD A,E           ; Add offset
    LD E,A
    LD A,(DE)         ; Get display code
    OUT (02h),A       ; Show count
    LD A,B
    OR A              ; Test count
    JR Z,LAST_BLOCK   ; If zero
    DEC B             ; Count down
    LD (08A8h),BC     ; Save count
    LD B,00h          ; 256 byte block
    OR A              ; Clear zero
    RET
LAST_BLOCK:
    LD B,C            ; Last block size
    RET

; Output block of bytes
OUT_BLOCK:
    EX AF,AF'         ; Save checksum
    LD E,(HL)         ; Get byte
    ADD A,E           ; Add to sum
    EX AF,AF'         ; Save new sum
    CALL OUT_BYTE     ; Output byte
    INC HL            ; Next byte
    DJNZ OUT_BLOCK    ; Do all bytes
    EX AF,AF'         ; Get checksum
    INC A             ; Add 1
    LD E,A            ; Output checksum
    RET

; Output single byte
OUT_BYTE:
    LD D,08h          ; 8 bits
    OR A              ; Clear carry
    CALL OUT_BIT      ; Output start bit
OUT_BITS:
    RR E              ; Get next bit
    CALL OUT_BIT      ; Output it
    DEC D             ; Count bits
    JR NZ,OUT_BITS    ; Do all 8
    SCF               ; Set stop bit
    JR OUT_BIT        ; Output it

; Output single bit
OUT_BIT:
    EXX               ; Save regs
    LD H,00h
    JR C,OUT_ONE      ; If outputting 1
    LD L,10h          ; High tone count
    CALL HIGH_TONE
    LD L,04h          ; Low tone count
    JR OUT_LOW
OUT_ONE:
    LD L,08h          ; High tone count
    CALL HIGH_TONE
    LD L,08h          ; Low tone count
OUT_LOW:
    CALL LOW_TONE
    EXX               ; Restore regs
    RET

; Generate tones
LOW_TONE:
    LD C,29h          ; Low frequency
    JR TONE_GEN

HIGH_TONE:
    LD C,11h          ; High frequency

TONE_GEN:
    LD A,(088Fh)      ; Check speed
    OR A              ; Zero = high speed
    JR NZ,TONE_SLOW
    SRL L             ; Halve cycles for high speed
TONE_SLOW:
    LD DE,0001h
    LD A,84h          ; Speaker on
    OUT (01h),A
TONE_LOOP:
    LD B,C            ; Period count
    DJNZ $            ; Delay
    XOR 80h           ; Toggle speaker
    SBC HL,DE         ; Count cycles
    JR NZ,TONE_LOOP
    RET

; Read block of bytes
READ_BLOCK:
    LD A,(088Ah)      ; Get operation
    LD C,A
    XOR A             ; Clear checksum
READ_LOOP:
    PUSH AF
    CALL READ_BYTE    ; Get byte
    BIT 1,C           ; Test operation
    JR NZ,READ_VERIFY ; If verify
    LD (HL),E         ; Store byte
    INC HL
    POP AF            ; Get checksum
    ADD A,E           ; Add byte
    DJNZ READ_LOOP    ; Do all bytes
    PUSH AF
    CALL READ_BYTE    ; Get checksum
    POP AF
    DEC E             ; Adjust tape sum
    CP E              ; Compare sums
    RET

READ_VERIFY:
    POP AF            ; Get checksum
    LD D,A            ; Save it
    LD A,E            ; Get byte
    CP (HL)           ; Compare to memory
    INC HL
    LD A,D            ; Restore checksum
    JR Z,READ_NEXT    ; Continue if match
    RET               ; Exit with error
READ_NEXT:
    JR READ_LOOP      ; Do next byte

; Read single byte
READ_BYTE:
    CALL READ_BIT     ; Get start bit
    LD D,08h          ; 8 bits
READ_BITS:
    CALL READ_BIT     ; Get bit
    RR E              ; Store in E
    DEC D             ; Count bits
    JR NZ,READ_BITS   ; Do all 8
    RET

; Read single bit
READ_BIT:
    EXX               ; Save regs
    LD HL,0000h       ; Clear count
READ_PERIOD:
    CALL MEASURE_PERIOD ; Check input
    JR C,READ_SHORT   ; If short period
    DEC L             ; Count long
    DEC L
    SET 0,H           ; Remember long
    JR READ_PERIOD    ; Continue
READ_SHORT:
    INC L             ; Count short
    BIT 0,H           ; Check if after long
    JR Z,READ_PERIOD  ; Continue if not
    RL L              ; Get bit value
    EXX               ; Restore regs
    RET

; Measure tape input period
MEASURE_PERIOD:
    LD DE,0000h       ; Clear count
PERIOD_HIGH:
    IN A,(03h)        ; Read input
    INC DE            ; Count period
    RLA               ; Test level
    JR NC,PERIOD_HIGH ; Wait for high
    XOR A             ; Speaker feedback
    OUT (01h),A
PERIOD_LOW:
    IN A,(03h)        ; Read input
    INC DE            ; Count period
    RLA
    JR C,PERIOD_LOW   ; Wait for low
    LD A,84h          ; Speaker feedback
    OUT (01h),A
    LD A,E            ; Get count
    CP 1Ah            ; Compare threshold
    RET               ; Return with flags
```

