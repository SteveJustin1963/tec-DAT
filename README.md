# tec-DAT TE-15, pg17, pg47 By Jim Robertson. 

Finally in issue 15 we get a D_isplay A_nd T_ape (DAT) data system; an LCD 16x2 ASCII characters and bit and character display with its own on board controller and an audio encoding and decoding program to save or load binary programs from audio cassette tape. It uses the JMON monitor code in ROM. 

![image](https://user-images.githubusercontent.com/58069246/194963611-d41bad0c-b4dc-4c26-b323-f16f9e48dcba.png)
![](https://github.com/SteveJustin1963/tec-DAT/blob/master/pics/ccxx33.png)
![](https://github.com/SteveJustin1963/tec-DAT/blob/master/pics/ccvv55.png)


### MENU DRIVER 
This is a universal routine used to select 
- It is already used by the tape software 
- various utilities routine from JMON. 
- It may also be easily used by the TEC user.

To move forward through the MENU, press "+". To move backward, press "-". Notice the automatic FIRST-TO-LAST, LAST-TO-FIRST wrap around. Pressing "GO" will take you into the perimeter handler.  When a "GO" command is received, control is passed to the required routine via a 2-byte address stored at 0888 by the calling routine.  


### Tape software
- Feature
 - 300 baud slow speed / 600 baud high speed/  auto execution 
 - LOAD ,  selected /  next /  at address 
 - TEST tape; with check every page (256 bytes) / to memory block / 

Access universal MENU driver and perimeter handler.  
Call up the cassette software by pressing SHIFT and ZERO together. If you have not fitted a shift key, the cassette software can be addressed by pressing the address key, then the plus key, then zero. 
 
- SAVE
  - displays -F aka File and a random two-byte, replace with file number press "+" key
  - now shows "-S". start of the block you wish to save(output to tape). Enter 0900, and then press "+". 
  - now shows "-E." enter the address of the last byte of the block to be saved. Enter 090A and press "+". 
  - now shows "-G". OPTIONAL AUTO-GO address, default FFFF - NON-ACTIVE aka. NO AUTO-GO upon a re-load. ANY other value entered here will result in an automatic execution upon a SUCCESSFUL LOAD AT THE ADDRESS ENTERED HERE
- press play and record on the tape recorder 
  - wait for the clear plastic leader to pass if at the start of a tape. Then press GO. 
  - The display will blank and a continuous tone will be heard from the speaker. After a few seconds the file information will be outputted and then a period of high frequency tone. This "middle sync" tone is to cover the time that the filename is displayed when reloading. 

- LOAD

- completion results showing:
  - END 
  - S (END SAVE); 
  - PASS CS (CHECK SUM); 
  - PASS Tb (TEST BLOCK); 
  - PASS LA (LOAD); 
  - FAIL CS (CHECK SUM); 
  - FAIL Tb (TEST BLOCK); 
  - FAIL Ld (LOAD). 

The one exception is when an auto execute is performed after a successful load. The tape software will display each file as it is found and also echo the tape signal. 






### Tape cct 

### JMON monitor code



## Theory on encoding for the tape part of DAT
This can be done by changing the amplitude, frequency or phase of a periodic repeating wave.

From www;
For example one approach is known as ASK, amplitude shift keying and this approach involves having a way that either has a positive amplitude or an amplitude of zero to encode the bits 1 and 0. 
```
s(t) = A cos(2 Pi Fc t), for 1 then A>0, 0 for A=0
```
The formula over time looks like this so s is the function for the signal voltage that is being transmitted and T is the current time of the transmission and if we are encoding a binary 1 at that time then the signal is some amplitude times cosine of 2 pi times some carrier frequency times the time. otherwise 0 is the voltage of
the signal so we can see what this looks like in the following example.

The delineation of each signal element I'll be encoding this binary string using amplitude shift keying so whenever there is a 0 we simply have a flat line of 0 voltage but whenever there is a 1 we will have some wave with the given amplitude. The number of ripples within a single signal element depends on what the carrier frequency is but it ultimately doesn't matter too much for how ASK works it's just a matter of a technical detail so here when we're encoding ones we have a wave that's fluctuating and then when we go back to 0 we have a flat line again then for the one will have wave again then flat for zero then waving for the one that's throughout here as well and etc.

This is not the only way to encode digital data using analog signals. Instead of changing the amplitude we could instead change the frequency and one scheme for doing this is BFSK, binary frequency shift keying. There's another scheme called MFSK, multi frequency shift keying where we can encode more signals in just zeros and ones but if we're only encoding zeros and ones we have a formula that looks like the following
```
s(t) = A cos(2 Pi Fc1 t) // digital 1 f1
s(t) = A cos(2 Pi Fc2 t) // digital 0 f2
```
This function like the previous one encodes the signal as a function of time and we still have an amplitude cosine and a 2pi the only difference between encoding a one or a zero is that the frequencies are different. We have one frequency that we'll use for encoding a binary 1 and a different frequency for encoding a binary 0.

We are not limited to using 2 frequencies we can actually create a scheme known as MFSK, multiple frequency shift keying and the formula looks like the following
```
s(t) = A cos(2 Pi Fci t) // 1<i<M 
```
Pick the values of `i` and the frequency in such a way that we span the range of possible values we're encoding so `i` will actually be in a given range and we will spread the frequencies out within that range to make sure that each of them is distinct. But as the number of different frequencies increases it increasingly is difficult to discern the distinction between different frequencies. There is a risk of having trouble discerning the signal.


Another way is BPSK, binary phase-shift keying, this approach is essentially same base formula as the others but now we will be changing the phase of our signal rather than the frequency or the amplitude. The formula looks like 
```
s(t) = A cos(2 Pi Fc t)      // digital 1 
s(t) = A cos(2 Pi Fc t + Pi) // digital 0
```
By adding in Pi we shift this signal to a different phase. We are once again using a carrier frequency but it will be the same frequency for both encoding a binary 0 and a binary 1 now. Because if you remember your trigonometric identities we can actually simplify this a bit further so when we want to encode a binary 0 we simply take the binary 1 signal and negate it and that is effectively the same as shifting the phase by PI. Therefore
```
s(t) =   A cos(2 Pi Fc t)  // digital 1 
s(t) = - A cos(2 Pi Fc t ) // digital 0
```
If we use a carrier frequency of 2 the result will look like

![](https://github.com/SteveJustin1963/tec-DAT/blob/master/pics/bpsk.jpg)

There are still other methods as well see https://en.wikipedia.org/wiki/Phase-shift_keying



### Other DAT PCB builds
- Brian Chiha
"Okay, me again!.  LCD Particle Physics on a TEC-1F.    If you would like an Ultimate Add-On Board for the TEC-1F (board only).  Message me.  $14 inc. postage.  I'm still working on a ROM for the board, I plan to include Disassembler, 8x8 Games and TE Magazine code + extras"

" Sneak peek at the TEC-1F Ultimate Expansion board, soon to be released. It is an all-in-one expansion for all your TEC needs.  It includes an 8x8 LED Matrix, LCD display, ROM/RAM Expansion, Single Stepping interrupts, and timed 5Hz-165Hz interrupts.
It plugs in directly on top of the TEC-1F via header pins.   Here are some pictures and a video showing how the stepper works. (this was requested).  Video also shows the LCD and 8x8 working. I'll prepare a ROM to go with BMON in the coming months."


![310139155_10162210872284056_4000640632497298524_n](https://user-images.githubusercontent.com/58069246/194762452-aedd2334-35ea-401c-b04e-906fa4b18579.jpg)
![310162465_10162210872249056_8638298831846877900_n](https://user-images.githubusercontent.com/58069246/194762468-8f4087ef-c286-4bac-91b6-9e306aab18c2.jpg)




- Ben Grimmett
![50480628_10155988682110869_7917208216545525760_n](https://user-images.githubusercontent.com/58069246/194762762-295da801-78b8-4ddc-8784-fa0a7b4743fa.jpg)



### Iterate

- https://www.facebook.com/groups/AusVintage/search/?query=DAT&epa=SEARCH_BOX
- analyze Jims comments on JMON code and flow chart the comments and code 
- explain how the systems work wrt DAT
- theory of presented methodology
- Screen upgrade
- LCD; 20 x 4 
- LCD 128 X 64 
- I2C OLED
- Composite Video
- VGA

### References
- https://hackaday.com/2018/10/07/reading-old-data-tapes-the-hard-way/
- https://github.com/SteveJustin1963/tec-MAGAZINES/blob/master/talking_electronics_15.pdf
- https://github.com/SteveJustin1963/tec-MONITOR
- https://easyeda.com/editor#id=5436587669434d578bdf98f6c96d4d5b




