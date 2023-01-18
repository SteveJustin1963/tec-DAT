# tec-DAT 
- TE-15 By Jim Robertson
  - pg17
  - pg47
- we get a D_isplay A_nd T_ape (DAT) data system; 
- need JMON monitor to run display at this stage of revision.

## DAT BOARD provides  
- 16x2 LCD display. It has an embedded controller as well.
- Cassette tape I/O interface.
- Single stepper module.
- 5 Buffered and latched input bits.
- 1 Inverter for general use.
- Diode clipped input line. (For RS232 input)
- MON select switch.


![image](https://user-images.githubusercontent.com/58069246/194963611-d41bad0c-b4dc-4c26-b323-f16f9e48dcba.png)
![image](https://user-images.githubusercontent.com/58069246/194963734-0883ac59-113a-43e6-a25a-58f0fb5ddad1.png)
![image](https://user-images.githubusercontent.com/58069246/194963815-36d04151-a8da-4b67-8188-45da40566032.png)


From the article…

### MENU DRIVER 
with JMON are 
- various utilities 
- and tape software 

To move forward through  MENU, press "+", backward, press "-". Notice wrap around of choices. Press "GO" takes you into the perimeter handler (sub menu).  press "GO" again then control is passed to required routine via a 2-byte address stored at 0888 by the calling routine.  


### Tape software
- Feature
 - 300 baud slow speed / 600 baud high speed/  auto execution 
 - LOAD ,  selected /  next /  at address 
 - TEST tape; with check every page (256 bytes) / to memory block / 
 - clock speed dependant, affects baud


Access universal MENU driver and perimeter handler.  
Call up the cassette software by pressing SHIFT and ZERO together. If you have not fitted a shift key, the cassette software can be addressed by pressing the address key, then the plus key, then zero. AD + 0
 
### SAVE
- now shows SAVE-H, high speed, press GO
- now shows hh-F, random two-byte, eg 4B-F, replace with file number say 00-F, press "+" key
- now shows "-S". start of the block you wish to save(output to tape). Enter 0900, and then press "+". 
- now shows "-E." enter the address of the last byte of the block to be saved. Enter 090A and press "+". 
- now shows "-G". OPTIONAL AUTO-GO address, default FFFF - NON-ACTIVE aka. NO AUTO-GO upon a re-load. ANY other value entered here will result in an automatic execution upon a SUCCESSFUL LOAD AT THE ADDRESS ENTERED HERE
- press play and record on the tape recorder 
- wait for the clear plastic leader to pass if at the start of a tape. Then press GO. 
- The display will blank and a continuous tone will be heard from the speaker. After a few seconds the file information will be outputted and then a period of high frequency tone. This "middle sync" tone is to cover the time that the filename is displayed when reloading. 
- After the high tone, the code will be outputted and also a digit will appear on the TEC LED display. This is the number of COMPLETE pages to be saved. In this case it will be zero
- When the code has been saved, a short end tone will be heard and then the menu will reappear with "-END-S", meaning end of save. Once the code has been saved, rewind the tape.  

### LOAD
- To reload the tape press the "+" key and you will see "SAVE-L" on the display, then "TEST-BL", "TEST-CS", then you will come to "LOAD-T" (for load tape). Note that there is no "TESTH" or "TEST-L" for low and high speeds as the test and load routine will load either speed automatically.  
- Press GO. The data display shows "- F' for file number. This will be as you left it when you saved. When loading or testing from tape, the file number here determines which file will be subject to the selected operation. If you enter FFFF here, the next file found will be used, regardless of its file number
- Next push "+". The data display will show "-S", meaning Start address. This is always set to H4114 by the software. The start address allows you to optionally load a file or test a file at an address different to the one on the tape, (which is the address from which it was saved). To demonstrate its operation and to make it a more convincing trial, we will enter 0A00. The file will now be loaded at 0A00. If you press the "+" key again, you will be back at the file name. (This last point demonstrates the programmable number of "windows" feature of the perimeter handler. It was set up for 2 "windows" by a short routine entered from the Menu driver before passing control to the Perimeter handler, remember that there was 4 "windows" when you saved the file). Now press GO

### Completion results
  - END 
  - S (END SAVE); 
  - PASS CS (CHECK SUM); 
  - PASS Tb (TEST BLOCK); 
  - PASS LA (LOAD); 
  - FAIL CS (CHECK SUM); 
  - FAIL Tb (TEST BLOCK); 
  - FAIL Ld (LOAD). 

The one exception is when an auto execute is performed after a successful load. The tape software will display each file as it is found and also echo the tape signal. 







