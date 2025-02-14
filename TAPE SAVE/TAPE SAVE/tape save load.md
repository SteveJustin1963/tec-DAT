
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

This covers everything from the highest level save/load operations down to the lowest level bit manipulation and tone generation needed for tape operations. All memory locations and port I/O operations are included.


```
;-----------------------------------------------
; TAPE SAVE/LOAD ROUTINES - COMPLETE LISTING
;-----------------------------------------------

;-----------------------------------------------
; SAVE ROUTINES
;-----------------------------------------------
; Save pre-amble - Sets up file information
SAVE_SETUP:           ; 0450-046F
    LD HL,(089E)      ; Get optional go address
    LD (08AA),HL      ; Store in output buffer
    LD HL,(089A)      ; Get start address
    LD (08A6),HL      ; Store in file info buffer
    EX DE,HL          ; Start address to DE
    LD HL,(089C)      ; Get end address
    OR A              ; Clear carry 
    SBC HL,DE         ; Calculate block size
    INC HL            ; Add 1 for count
    JP C,004A         ; If end < start, error
    LD (08A8),HL      ; Store byte count
    LD HL,(0898)      ; Get file number
    LD (08A4),HL      ; Store in info block
    JP SAVE_MAIN      ; Go to main save routine

; Main save routine
SAVE_MAIN:           ; 04F0-052E 
    LD HL,3000        ; Leader cycles
    CALL LOW_TONE     ; Output leader
    LD HL,08A4        ; Point to file info
    LD B,0C           ; 12 bytes to output
    XOR A             ; Clear checksum
    CALL OUT_BLOCK    ; Output file info
    LD HL,5000        ; Mid sync cycles
    CALL HIGH_TONE    ; Output sync
    LD HL,(08A6)      ; Get data start address

SAVE_LOOP:
    LD BC,(08A8)      ; Get byte count
    CALL CONVERT_BLOCK ; Convert for display
    JR NZ,SAVE_BLOCK  ; If full block
    LD A,B            ; Check remaining
    OR A
    JR Z,SAVE_END     ; If done
    XOR A             ; Flag last block

SAVE_BLOCK:
    PUSH AF           ; Save status
    EXX
    LD HL,0214        ; Short sync
    CALL HIGH_TONE
    EXX
    XOR A             ; Clear checksum
    CALL OUT_BLOCK    ; Output block
    POP AF
    JR NZ,SAVE_LOOP   ; Continue if more

SAVE_END:
    LD HL,1000        ; End tone length
    CALL HIGH_TONE    ; Output end marker
    LD A,05           ; End display
    JP 03E6           ; Return to menu

;-----------------------------------------------
; LOAD ROUTINES
;-----------------------------------------------
; Main load routine
LOAD_START:          ; 0531-05B4
    LD BC,1000        ; Leader detect count

LOAD_DETECT:
    CALL MEASURE_PERIOD ; Check input
    JR C,LOAD_START   ; Retry if no leader
    DEC BC            ; Count cycles
    LD A,B
    OR C              ; Check if enough
    JR NZ,LOAD_DETECT

    LD B,0C           ; 12 bytes to read
    LD HL,08A4        ; File info buffer
    CALL MEASURE_PERIOD ; Wait for sync
    JR NC,LOAD_DETECT
    CALL READ_BLOCK   ; Get file info
    JR NZ,LOAD_FAIL   ; Exit if error

    LD HL,(0898)      ; Get wanted file number  
    INC HL
    LD A,H
    OR L              ; Check if FFFF
    DEC HL
    JR Z,LOAD_DATA    ; Accept any file
    LD DE,(08A4)      ; Get tape file number
    OR A
    SBC HL,DE         ; Compare numbers
    JR NZ,LOAD_START  ; Try next if no match

LOAD_DATA:
    LD BC,(08A8)      ; Get byte count
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
CONVERT_BLOCK:       ; 05C9-05E2
    LD A,B            ; Get count
    AND 0F            ; Mask to digit
    LD DE,07D0        ; Display table
    ADD A,E           ; Add offset
    LD E,A
    LD A,(DE)         ; Get display code
    OUT (02),A        ; Show count
    LD A,B
    OR A              ; Test count
    JR Z,LAST_BLOCK   ; If zero
    DEC B             ; Count down
    LD (08A8),BC      ; Save count
    LD B,00           ; 256 byte block
    OR A              ; Clear zero
    RET
LAST_BLOCK:
    LD B,C            ; Last block size
    RET

; Output block of bytes
OUT_BLOCK:          ; 064A-0656
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
OUT_BYTE:           ; 0657-0665
    LD D,08           ; 8 bits
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
OUT_BIT:            ; 0666-067F
    EXX               ; Save regs
    LD H,00
    JR C,OUT_ONE      ; If outputting 1
    LD L,10           ; High tone count
    CALL HIGH_TONE
    LD L,04           ; Low tone count
    JR OUT_LOW
OUT_ONE:
    LD L,08           ; High tone count
    CALL HIGH_TONE
    LD L,08           ; Low tone count
OUT_LOW:
    CALL LOW_TONE
    EXX               ; Restore regs
    RET

; Generate tones 
LOW_TONE:           ; 0680-0682
    LD C,29           ; Low frequency
    JR TONE_GEN

HIGH_TONE:          ; 0684-0685
    LD C,11           ; High frequency

TONE_GEN:           ; 0686-069E
    LD A,(088F)       ; Check speed
    OR A              ; Zero = high speed
    JR NZ,TONE_SLOW
    SRL L             ; Halve cycles for high speed
TONE_SLOW:
    LD DE,0001
    LD A,84           ; Speaker on
    OUT (01),A
TONE_LOOP:
    LD B,C            ; Period count
    DJNZ $            ; Delay
    XOR 80            ; Toggle speaker
    SBC HL,DE         ; Count cycles
    JR NZ,TONE_LOOP
    RET

; Read block of bytes
READ_BLOCK:         ; 05E3-05FD
    LD A,(088A)       ; Get operation
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
READ_BYTE:          ; 060B-0617
    CALL READ_BIT     ; Get start bit
    LD D,08           ; 8 bits
READ_BITS:
    CALL READ_BIT     ; Get bit
    RR E              ; Store in E
    DEC D             ; Count bits
    JR NZ,READ_BITS   ; Do all 8
    RET

; Read single bit
READ_BIT:           ; 0618-062F
    EXX               ; Save regs
    LD HL,0000        ; Clear count
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
MEASURE_PERIOD:     ; 0630-0649
    LD DE,0000        ; Clear count
PERIOD_HIGH:
    IN A,(03)         ; Read input
    INC DE            ; Count period
    RLA               ; Test level
    JR NC,PERIOD_HIGH ; Wait for high
    XOR A             ; Speaker feedback
    OUT (01),A
PERIOD_LOW:
    IN A,(03)         ; Read input
    INC DE            ; Count period
    RLA
    JR C,PERIOD_LOW   ; Wait for low
    LD A,84           ; Speaker feedback
    OUT (01),A
    LD A,E            ; Get count
    CP 1A             ; Compare threshold
    RET               ; Return with flags
```
