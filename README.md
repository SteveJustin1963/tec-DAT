 # tec-DAT The original
https://github.com/SteveJustin1963/tec-BOOKS/blob/master/TE/Mag/talking_electronics_15.pdf


![image](https://user-images.githubusercontent.com/58069246/194963815-36d04151-a8da-4b67-8188-45da40566032.png)

![image](https://user-images.githubusercontent.com/58069246/213081798-252876b8-6f4e-4a38-9460-87574991418e.png)





TE-15 pg17 and pg47

- we get a 2 line LCD Display (2x16) and a audio tape interface (audio jack) to tape casette deck 
- code is in the JMON monitor

![image](https://user-images.githubusercontent.com/58069246/194963734-0883ac59-113a-43e6-a25a-58f0fb5ddad1.png)


 

![image](https://user-images.githubusercontent.com/58069246/213082340-afe1e256-bc56-4e52-adf9-4756c938b9f0.png)

![image](https://user-images.githubusercontent.com/58069246/213083879-92184a62-b5b7-47d5-8ae6-df6216d9864b.png)

![image](https://user-images.githubusercontent.com/58069246/213081906-802e885e-6195-4ec0-a6f7-d8fb87a7deda.png)

![image](https://user-images.githubusercontent.com/58069246/213082010-15d121a9-a9f3-4754-85ba-6d49dc45afff.png)

 
```
                   POWER ON/RESET
                         │
                         ▼
                   Initialize JMON
                   [0000-006A]
                         │
                         ▼
              Save Registers & Setup
                   [006B-008F]
                         │
                         ▼
     ┌────────────────────────────────────┐
     │           Main Loop                │
     │    Update Display [00B2-00E1]      │
     └─────────────┬──────────────────────┘
                   │
                   ▼
            Check Input Mode
                   │
         ┌─────────┴─────────┐
         ▼                   ▼
    Data Mode           Address/Function Mode
    [00D0-00E1]         [0102-017F]
         │                    │
         │                    │
    ┌────┴────────────────────┘
    │
    ▼
Process Key Input [0181-01E5]
    │    
    ├─── "+" Key: Increment address
    │    
    ├─── "-" Key: Decrement address
    │    
    ├─── "GO" Key: Execute at current address
    │    
    ├─── "AD" Key: Return to monitor
    │    
    └─── Data Keys: Enter data at current address
         │
         ▼
    Auto-increment?
         │
    ┌────┴────┐
    │         │
    ▼         ▼
   Yes        No
   │          │
   │          └───────┐
   ▼                  ▼
Inc Address    Stay at Current Address
   │                  │
   └──────────────────┘
         │
         ▼
    Back to Main Loop
```

```
LED Display Scan Routine [01BA-01D4]
    │
    ├─── Initialize scan bit
    ├─── Output segment data
    ├─── Output scan bit
    ├─── Delay
    └─── Move to next digit

Key Input Processing [06AD-06D4]
    │
    ├─── Detect key press
    ├─── Debounce
    ├─── Validate
    └─── Process auto-repeat

LCD Interface [023C-026B]
    │
    ├─── Initialize LCD
    ├─── Check busy flag
    ├─── Send commands
    └─── Display data

Tape Operations [04F0-05FD]
    │
    ├─── Write leader
    ├─── Write data blocks
    ├─── Calculate checksums
    ├─── Read data
    └─── Verify checksums
```

```
POWER ON/RESET [0000]
                         │
                         ▼
              Initialize JMON [0000-006A]
              Save Registers [006B-008F]
                         │
                ┌────────┴──────────┐
                ▼                   ▼
         Normal Monitor        SHIFT+0 or AD+0
         Operations            (Tape Software)
         │                         │
    ┌────┴────┐             ┌──────┴──────┐
    ▼         ▼             ▼             ▼
Update     Process      MENU DRIVER    Hardware
Display    Keys         [03E3]        Control
[00B2]     [0181]           │             │
    │         │        ┌────┴────┐        │
    └────┬────┘        ▼         ▼        │
         │          Forward    Backward   │
         │            (+)       (-)       │
         │             │         │        │
         │             └────┬────┘        │
         │                  ▼             │
         │       ┌─────────────────┐      │
         │       │Perimeter Handler│      │
         │       │     [0479]      │      │
         │       └────────┬────────┘      │
         │                ▼               │
         │         Parameter Entry        │
         │         [04F0-04FF]            │
         │               │                │
         │          ┌────┴────┐           │
         │          ▼         ▼           │
         │        SAVE       LOAD         │
         │         │          │           │
         │    ┌────┴────┐  ┌──┴───┐       │
         │    │  [0686] │  │[0630]│       │
         │    │Tone Gen │  │Decode│       │
         │    └────┬────┘  └──┬───┘       │
         │         │         │            │
         │    ┌────┴────┬────┴───┐        │
         │    ▼         ▼        ▼        │
         │  High      Low     Checksum    │
         │  [0684]   [0680]  Verify       │
         │    │         │     [04F0]      │
         │    └────┬────┘      │          │
         │         ▼           │          │
         │    Data Blocks      │          │
         │    (256 bytes)      │          │
         │         │           │          │
         │         └─────┬─────┘          │
         │               ▼                │
         │      Status Display            │
         │      [05A1-05B4]               │
         │               │                │
         └───────────────┴────────────────┘

Hardware Control Layer:
----------------------
┌─────────────────────────────────┐
│ Display Buffer [082C/D]         │
│ LED Control [01BA-01D4]         │
│ Speaker Output [0680-0686]      │
│ Keyboard Input [0820]           │
│ Tape Interface [04F0-05FD]      │
└─────────────────────────────────┘

Memory Management:
-----------------
┌─────────────────────────────────┐
│ Current Edit Location [082E]    │
│ Monitor Control Byte [082B]     │
│ Auto Key Status [082A]          │
│ Key Press Flag [0825]           │
└─────────────────────────────────┘
```



## MENU DRIVER 
- various utilities 
- and tape software 
- To move forward through  MENU, press "+",
- backward, press "-".
- Notice wrap around of choices.
- Press "GO" takes you into the perimeter handler (sub menu).
- press "GO" again then control is passed to required routine via a 2-byte address stored at 0888 by the calling routine.  


# Tape software
- 300 baud slow speed / 600 baud high speed/  auto execution 
- LOAD ,  selected /  next /  at address 
- TEST tape; with check every page (256 bytes) / to memory block / 
- clock speed dependant, affects baud
- To access universal MENU driver and perimeter handler.
- Call up the cassette software by pressing SHIFT and ZERO together.
- If you have not fitted a shift key, the cassette software can be addressed by pressing the address key, then the plus key, then zero. AD + 0
 
## SAVE
- now shows SAVE-H, high speed, press GO
- now shows hh-F, random two-byte, eg 4B-F, replace with file number say 00-F, press "+" key
- now shows "-S". start of the block you wish to save(output to tape). Enter 0900, and then press "+". 
- now shows "-E." enter the address of the last byte of the block to be saved. Enter 090A and press "+". 
- now shows "-G". OPTIONAL AUTO-GO address, default FFFF - NON-ACTIVE aka. NO AUTO-GO upon a re-load.
- ANY other value entered here will result in an automatic execution upon a SUCCESSFUL LOAD AT THE ADDRESS ENTERED HERE
- press play and record on the tape recorder 
- wait for the clear plastic leader to pass if at the start of a tape. Then press GO. 
- The display will blank and a continuous tone will be heard from the speaker. After a few seconds the file information will be outputted and then a period of high frequency tone. This "middle sync" tone is to cover the time that the filename is displayed when reloading. 
- After the high tone, the code will be outputted and also a digit will appear on the TEC LED display. This is the number of COMPLETE pages to be saved. In this case it will be zero
- When the code has been saved, a short end tone will be heard and then the menu will reappear with "-END-S", meaning end of save. Once the code has been saved, rewind the tape.  

## LOAD
- To reload the tape press the "+" key and you will see "SAVE-L" on the display, then "TEST-BL", "TEST-CS", then you will come to "LOAD-T" (for load tape). Note that there is no "TESTH" or "TEST-L" for low and high speeds as the test and load routine will load either speed automatically.  
- Press GO. The data display shows "- F' for file number. This will be as you left it when you saved. When loading or testing from tape, the file number here determines which file will be subject to the selected operation. If you enter FFFF here, the next file found will be used, regardless of its file number
- Next push "+". The data display will show "-S", meaning Start address.
- This is always set to H4114 by the software.
- The start address allows you to optionally load a file or test a file at an address different to the one on the tape, (which is the address from which it was saved).
- To demonstrate its operation and to make it a more convincing trial, we will enter 0A00.
- The file will now be loaded at 0A00.
- If you press the "+" key again, you will be back at the file name. (This last point demonstrates the programmable number of "windows" feature of the perimeter handler.
- It was set up for 2 "windows" by a short routine entered from the Menu driver before passing control to the Perimeter handler, remember that there was 4 "windows" when you saved the file).
- Now press GO

## Completion results
- END 
- S (END SAVE); 
- PASS CS (CHECK SUM); 
- PASS Tb (TEST BLOCK); 
- PASS LA (LOAD); 
- FAIL CS (CHECK SUM); 
- FAIL Tb (TEST BLOCK); 
- FAIL Ld (LOAD). 
- The one exception is when an auto execute is performed after a successful load. The tape software will display each file as it is found and also echo the tape signal. 


# JMON monitor  

## overall process 

The tone encoding used in this code is Manchester encoding. It is a type of digital encoding in which data is encoded by the presence or absence of a transition (or edge) in the signal. In this code, a low frequency tone is used to represent a binary 0, and a high frequency tone is used to represent a binary 1. The tone routine L0686 uses the value in register C to determine whether to output a low or high frequency tone. The value in register L is used to control the duration of the tone, and is halved if the low-speed save option is enabled.

- Prepare the data to be saved
- Format the tape
- Calibrate the tape drive
- Run the Save Routine Preamble which shifts the file number, start address, and optional go address across to the Tape File Information Block, calculates the length of the block and transfers it to the Tape File Information Block, and check if the end address is lower than the start address, the routine will jump to display an error message
- Final Tape Set-up by placing FFFF in the optional go window before entering the perimeter handler
- Run the Tape Output Routine which outputs a leader of low frequency tone, the File Information Block, several seconds of high frequency middle sync, breaks the data up into blocks of 256 bytes and outputted with a checksum at the end of each block, showing a counter on the TEC LED display showing the number of complete blocks left, outputting an end of file high frequency tone at the end.
- Input the tape by running the Tape Input Loop which detects a valid leader by counting 1000 cycles of low frequency tone, waits until it detects the start bit of the File Information Block, loads the block in and does a checksum compare, tests the file number window, and the optional start window, then loads and tests the data blocks, verifies that the correct number of bytes have been read in and loaded, clears the Tape File Information Block and the optional go address, checks that the end address is not lower than the start address, and jumps to the next operation or returns to the main program.

##  more detailed
1. The Save Routine Preamble:
- Shifts the file number, start address, and optional go address across to the Tape File Information Block
- Calculates the length of the block and transfers it to the Tape File Information Block
- If the end address is lower than the start address, the routine will jump to display an error message

2. Final Tape Set-up:
- Places FFFF in the optional go window before entering the perimeter handler

3. Tape Output Routine:
- Outputs a leader of low frequency tone
- Outputs the File Information Block
- Outputs several seconds of high frequency middle sync
- The data is broken up into blocks of 256 bytes and outputted with a checksum at the end of each block
- A counter is shown on the TEC LED display showing the number of complete blocks left
- If there is an odd-sized block, it is outputted as the last block
- Outputs an end of file high frequency tone at the end.

4. Tape Input Loop:
- Detects a valid leader by counting 1000 cycles of low frequency tone
- Waits until it detects the start bit of the File Information Block
- The block is loaded in and a checksum compare is done
- If an error is detected, the routine jumps to display "FAIL -XX", otherwise the file number is converted to display format and displayed for a few seconds.
- Test is done on the required file number window, if it is FFFF, the routine skips ahead to load/test the file.
- Otherwise, the required file number is subtracted from the just loaded file number.
- If the result is zero, then the file is the one selected and is loaded/tested.
- The optional start window is tested for FFFF.
- If it is, the start address from the tape is used.
- If the optional start buffer has something other than FFFF, then the address here is used as the start address to load/test the tape.
- The Tape Input Routine loads and tests the data blocks from the tape.
- The blocks of data are read in and checked for errors using the checksum at the end of each block.
- A counter is shown on the TEC LED display showing the number of complete blocks left to be read in.
- If there is an odd-sized block, it is read in as the last block.
- After all the blocks have been read in, the routine checks for the end of file high frequency tone.
- If the tone is not detected, the routine will jump to display an error message.
- The routine verifies that the correct number of bytes have been read in and loaded
- Clears the Tape File Information Block and the optional go address
- The end address is checked against the start address, if end is lower than start, the routine will jump to display an error message.
- The routine then jumps to the next operation or returns to the main program.



## tones generating and decoding
- tones are generated using a software-based approach. The code uses two routines, L0684 and L0680, to output high and low tones respectively. These routines take a single argument, the duration of the tone in machine cycles.
- The high tone routine (L0684) loads the value 11H into register C and then jumps to the tone generation routine L0686. The low tone routine (L0680) loads the value 0x29 into register C and then jumps to the same tone generation routine L0686.
- The tone generation routine L0686 checks if the save is in low speed and if so, it halves the cycle count in L. It then repeatedly outputs a square wave on the speaker by toggling the speaker bit in a port and delaying for the number of cycles specified in C.
- Decoding the tones is done in another routine, L0630. This routine waits for the signal to change from high to low and then measures the duration of the low signal.
- Depending on the duration of the low signal, the routine can determine if the incoming signal is a binary 0 or a binary 1.
- In the code provided, the high tone corresponds to a binary 1 and the low tone corresponds to a binary 0.
- Once the tones are decoded, they are used to reconstruct the file information block that was previously saved on tape.

## L0684 
- is a label that marks the location in memory where the routine starts
- The instruction "LD C, 11H" loads the value 11H (decimal 17) into the C register. This value represents the number of cycles that the high tone will be played for
- The instruction "CALL L0684" transfers program execution to the L0684 routine (in this case, it is the same as the instruction "JR L0686")
- The instruction "LD C, 11H" sets the cycle count for the high tone.
- The instruction "JR L0686" jumps to the subroutine L0686, where the tone is generated.

## L0680
- Load register C with the value 0x29 (41 in decimal)
- Jump to the tone routine (L0686)
- The L0680 routine sets up for generating a low tone (long period) by loading the value 0x29 (41 in decimal) into register C. This value will be used as a delay in the tone routine (L0686) to generate the low tone.

## L0686:
- Loads the value 29 into register C
- Jumps to the "tone routine" at L0686

## L0680:
- Loads the value 29 into register C
- Jumps to the "tone routine" at L0686 (identical to the instruction at L0686)
- As for the tone routine, It is responsible for producing the tone for the tape. 
  - The routine at L0686 sets up the length of the tone, either low or high, by loading the value of the cycle count into register C. 
  - At L0680, it sets up a low tone (long period) and at L0684, it sets up a high tone (short period). 
  - The tone is produced by outputting a square wave to the speaker, with a cycle count specified by the value in register C, the delay between each change of the wave is generated by DJNZ instruction. 
  - It tests for low speed save and if so, it halves the cycle count in L. Finally it returns to the calling routine.

## L0630:
- Calls a period routine to determine the duration of a tone.
- If the tone is a low tone, it jumps to L0531.
- If the tone is high tone, it decrements the value in register BC.
- Then it checks if the value in BC is zero.
- If it is not zero, it loops back to call the period routine again.
- If it is zero, it indicates that a valid file follows and continues with the next instruction.

## L0531: 
- Routine to load and check a file information block from tape
- Initialize BC register with value 0x1000 to count number of cycles
- Call L0630 (Period) routine
- Loop until low tone is detected, decrement BC and check if it reaches zero
- If BC reaches zero, continue to next step.
- Load B with value 0x0C and HL with value 0x08A4, pointer to file information block input buffer.
- Call L0630 (Period) routine and wait for low tone to end
- Call L05E7 (Inblock) to get file information block
- If there is an error, jump to L05A1 (Fail load routine)
- Else, load BC with value 0x0800 to point to display buffer
- Load HL with value from L08A4 (file number) and call L0830 (Convert) to convert HL to display code
- Load A with value 0x47 and put "F" in display buffer for "File"
- Load BC with value 0x01F2 (display on time)
- Push BC to stack, call L0836 (Scan) and pop BC
- Decrement BC and check if it is zero, if not loop back to step 13.




## DAT BOARD Providers  
- 16x2 LCD display. It has an embedded controller as well.
- Cassette tape I/O interface.
- Single stepper module.
- 5 Buffered and latched input bits.
- 1 Inverter for general use.
- Diode clipped input line. (For RS232 input)
- MON select switch.

Plenty of tec nuts have played and built the dat and the lcd display and more
- https://www.facebook.com/groups/623556744820045/search/?q=dat
- https://www.facebook.com/groups/623556744820045/search/?q=lcd
- etc
 
## Ben Grimmett
![image](https://user-images.githubusercontent.com/58069246/213084866-9ef37d49-0787-4bee-8c27-a3b632ddba68.png)

- uses z80 socket
- allows room for eprom emulator board
- removed 5 digital inputs

## Brian Chiha
![310139155_10162210872284056_4000640632497298524_n](https://user-images.githubusercontent.com/58069246/194762452-aedd2334-35ea-401c-b04e-906fa4b18579.jpg)
![310162465_10162210872249056_8638298831846877900_n](https://user-images.githubusercontent.com/58069246/194762468-8f4087ef-c286-4bac-91b6-9e306aab18c2.jpg)

- called the "Ultimate Add-On Board for the TEC-1F"
- board only for $14 (usd) including postage
- software will include ROM called "BMON"
  - Disassembler 
  - 8x8 Games 
  - TE Magazine code + extras in the ROM
- hardware
  - "all-in-one expansion" for the TEC-1F includes 
  - 8x8 LED Matrix
  - LCD display
  - ROM/RAM Expansion
  - Single Stepping interrupts
  - timed 5Hz-165Hz interrupts.
  - plugs in directly on top of the TEC-1F via header pins

