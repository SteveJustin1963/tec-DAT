# tec-DAT
A TEC-1 Digital Audio Tape data system and LCD display, for saving or playback of programs and displaying 16x2 ASCII characters.  
By Jim Robertson

## From TE-15 

SENDING IN PROGRAMS VIA TAPE 

We are looking forward to readers sending programs to us. ... Provide us with a copy of the program. Save it on tape with a crystal speed of half 3.58MHz. ... We also need documentation on the program. Write what it does and where it runs in memory and include any notes you may have generated. The first thing we will do is disassemble it and load it into our IBM clone. Here we can format it for publishing. For the sake of our disassembler, please, if you can, put tables at the end of the program code and write down where the tables are located. This way we can use our HEX dump routine and tack the tables on at the end of the code.

JMON UP-GRADES (parts omitted, see full article)

JMON has been designed to be upgraded without losing software compatibility. Some likely changes are the removal of the low speed tape save (unless there is a storm of protest). This will decrease the software overhead in the tone routine and even-up the period measurement. The result will be an increase in the tolerance of different TEC frequencies and different tape speeds. This should make it possible to freely interchange half 3.58MHz and half 4.MHz tape software as well as allowing poorer quality tape players to be used. The single stepper, which has no effect on the MONitor at all, may be shifted to a more specialized ROM to increase the stepper's abilities.- The keyboard and LCD RST's will not be changed, so any routine you write using these will run on future up-grades. The same cannot be said if you directly call into JMON. So don't do it! 

![](https://github.com/SteveJustin1963/tec-DAT/blob/master/dat-15-17.png)

THE TAPE SOFTWARE

The TAPE SAVE facility is versatile and reliable. Some of the functions include: 
* 300 and 600 baud tape SAVE, 
* auto execution, * LOAD selected file, 
* LOAD next file, * LOAD at optional address, 
* TEST tape to memory block 
* TEST tape check sum. 

Both tests may be combined with other options. The tape software uses the universal MENU driver and perimeter handler. These routines allow easy selection of cassette functions (e.g. Load, Save, etc.) and easy passing of variables to the tape software. The tape software contains check-sum error detection that allows the user to know if the load has failed. A checksum compare is performed after every page (256 bytes) and also after the leader is loaded. This means the user does not need to wait until the end of a load or test for error detection. Each full page to be loaded, tested or saved, is displayed on the TEC LED display. Up to 16 pages are displayed. Upon completion of a tape operation, the MENU is re-entered with an appropriate display showing:
* -END -S (END SAVE); 
* PASS CS (CHECK SUM); 
* PASS Tb (TEST BLOCK); 
* PASS LA (LOAD); 
* FAIL CS (CHECK SUM); 
* FAIL Tb (TEST BLOCK); 
* FAIL Ld (LOAD). 

The one exception is when an auto execute is performed after a successful load. The tape software will display each file as it is found and also echo the tape signal.

from page 22...

THE TAPE SYSTEM / TEC CONSIDERATIONS

The tape software works on any type of TEC, the only consideration is the various different clock speeds. The following description generally applies to TEC's with a crystal oscillator that is fitted with a colour burst (3.58MHz) crystal and divide-by-two stage. If you are still using a 4049 based oscillator, the tape system will work ok, but it will be very important to note the TEC clock speed when saving as the TEC must be set to the same speed when re-loading. Another problem can be the drift in frequency over a temperature range and the different oscillator frequencies between TEC's. When saving a tape, the best idea is to wind the clock up to full speed, and then turn back the speed control pot one quarter of a turn. This will allow you compensate for speed drift if ever required. The tape also works very reliably with a 4MHz crystal and divide by two stage, however a tape written using a 3.58MHz oscillator cannot be loaded by a TEC that uses a 4MHz oscillator, and vice versa. If you are sending programs into TE on tape, they must be recorded with the 3.58MHz crystal. (divided by two). The tape system has been extensively tested and found to be very reliable under a wide range of conditions. We don't expect you to have any trouble in getting it to work reliably for yourself. 

To start with, you need a JMON monitor ROM as the tape software is inside this ROM. Secondly, you will need a cassette recorder with both "mic" and "ear" sockets. Any audio cassette player of reasonable quality should be ok, provided it has the two sockets mentioned above. We have tested more than six types, and found them to be quite suitable. Thirdly, you will need to have constructed the cassette interface on the LCD interface board and have made up the two connecting cables, with 3.5mm plugs on each end. Finally you will need a new C60 or C90 cassette of the better quality types, such as TDK or Sony. We found the cheap tapes from the junk shops or supermarkets to be unreliable. (Some of them didn't work AT ALL, so don't take the chance). Now connect the "mic" on the tape recorder to the "tape out" from the TECand "ear" socket to the "tape-in" on the TEC. (It's a good idea to mark the cables between the recorder and the TEC to prevent incorrectly connecting the leads). Insert a tape and we are ready to learn how to operate the system. 

HOW TO OPERATE THE TAPE SYSTEM.

We will start by saving a few bytes at 0900. 

Enter at 0900 the following: 

01 02 03 04 05 06 07 08 09 0A. OK. 

Now connect up the tape recorder as described above and call up the tape software by pushing shift and zero at the same time or Address, "+","0" consecutively. The TEC display will now show "SAVE-H" and this is the heading for SAVE at HIGH SPEED. Now select this by hitting "GO" The display will now have a random two-byte value in the address display and "-F' in the data display. The "-F' in the data display is for the file number, while the address number is just junk from the RAM. You can enter a file number by pressing the data keys. Enter anything you want. The numbers you enter will shift across in the same fashion as when entering an address on the MONitor. Then when you have entered a file number, press the "+" key. The data display will now show "-S". This is where you enter the start of the block you wish to output. Enter 0900, and then press "+". The data displays now show "-E." This is where you enter the address of the last byte of the block to be saved. Enter 090A and press "+". The next data display is "-G". This is the OPTIONAL AUTO-GO address, this is always set to FFFF by the software as this is its NON-ACTIVE state, i.e. NO AUTO-GO upon a re-load. ANY other value entered here will result in an automatic execution upon a SUCCESSFUL LOAD AT THE ADDRESS ENTERED HERE. We don't require auto execution, so leave this at FFFF. Now press play and record on the tape recorder and wait for the clear plastic leader to pass if at the start of a tape. Incidentally, it is not a good idea to remove this leader as has been advised in another magazine, as it protects the tape from stretching and possibly breaking, when rewound. When the tape is right, press GO. The display will blank and a continuous tone will be heard from the speaker. After a few seconds the file information will be outputted and then a period of high frequency tone. This "middle sync" tone is to cover the time that the filename is displayed when re-loading.   

After the high tone, the code will be outputted and also a digit will appear on the TEC LED display. This is the number of COMPLETE pages to be saved. In this case it will be zero. A point to raise here is that if you ever accidentally enter a start address that is HIGHER than the end address, when GO is pressed, the software will detect this and display "Err-In". In this case, Push "+" or "-" to go back to the perimeter handler where you can correct the error. When the code has been saved, a short end tone will be heard and then the menu will re-appear with "-END-S", meaning end of save. Once the code has been saved, rewind the tape. To re-load the tape press the "+" key and you will see "SAVE-L" on the display, then "TEST-BL", "TEST-CS", then you will come to "LOAD-T" (for load tape). Note that there is no "TESTH" or "TEST-L" for low and high speeds as the test and load routine will load either speed automatically. Press GO. The data display shows "- F' for file number. This will be as you left it when you saved. When loading or testing from tape, the file number here determines which file will be subject to the selected operation. If you enter here, the next file found will be used, regardless of its file number. For now, we will leave it as it is. Next push "+". The data display will show "-S", meaning Start address. This is always set to H4114by the software. The start address allows you to optionally load a file or test a file at an address different to the one on the tape, (which is the address from which it was saved). To demonstrate its operation and to make it a more convincing trial, we will enter 0A00. The file will now be loaded at 0A00. If you press the "+" key again, you will be back at the file name. (This last point demonstrates the programmable number of "windows" feature of the perimeter handler. It was set up for 2 "windows" by a short routine entered from the Menu driver before passing control to the Perimeter handler, remember that there was 4 "windows" when you saved the file). Now press GO. The display will blank. Now start the tape playing. The sound from the tape will be echoed on the TEC speaker. Soon the leader will be heard and it should sound as crisp as when it was saved. If not, experiment with the volume. The interface allows for a wide variation of volumes but 3/4 volume is a good place to start. After the leader has passed, the file name is loaded and should appear on the display. If it was not correctly loaded, "FAIL-Ld" will appear. In this case experiment with the volume and retry. After a few seconds the file name disappears and the number of complete pages to load are displayed on the middle digit. The code is now being loaded. The code is loaded very quickly and hopefully a "PASS-Ld" will appear. If not, re-try with a different volume setting. After you have successfully loaded, hit reset and ADdress 0A00 and 01, 02 etc. will be found. If you are unable to get a successful load after many attempts, then skip ahead to the trouble shooting section. Now we have a successful load, we will experiment with the TEST BLOCK function. Change a byte in the 0A00 block. Now call up the tape software (Shift-0, or ADdress, "+" ,0), select "TEST-BL", and LEAVE F1-41+ at the optional start. ("-S") Then rewind the tape and play it back like you did when loading. At the end of the test, the display comes back with "PASS-TB". Now do this again, but this time enter 0A00 at the optional start and F141-it. for the file. This will demonstrate the load/test next file feature. Because 0A00 has been entered in the optional start "window", the test will be between tape and the code at 0A00. Rewind the tape and press "GO" on the TEC, then play the tape. Because a byte has been changed, the test this time will fail and the display will show "FAIL-TB." Use the test-block feature whenever you wish to compare a tape file with a memory block or test that a save operation was successful. If ever revising software on a tape of which you do not have a copy in memory, use the test checksum (TESTCS) to ensure that the file is good. By use of the "LOAD NEXT FILE" feature (F1-14F in the file number window) you can go through a tape completely, checking each file. THE "AUTO-GO" To use the Auto-GO feature, you must enter the required GO address WHEN YOU SAVE THE FILE. The go address is entered under the "-G" data display.
Experiment with the following: 

0900: 21 10 09 11 00 08 01 06

0908: 00 ED B0 CD 36 08 18 FB

0910: 6F EA C6 EB E3 EB.

Save this as described above, but this time enter 0900 under the "-S" heading, 0921 under "-E", and 0900 under "-G". Now re-load it and if the load is successful, the program will start automatically and an appropriate display message will appear. 

USING THE TAPE SYSTEM. 

The primary use for your tape save system is as a mass storage device for your files. Files may be saved and loaded as described previously, the important addition here is good paper-work habits. It is very important to keep a log of your files or you will quickly forget what you have, where it is located, and you will end up writing over your files! Your log system must include identifying each cassette and the side of the tape, the files on the cassette in the correct order, how many of each file, the date and any notes on the file. If your recorder has a tape counter facility, it makes good practice to record the readings from this, so that files may be quickly found anywhere on the tape. Also a great aid is to log approximately the location of each file e.g. half-way, 30 seconds from rewind from end etc. Apply the above idea to the start of vacant area on the tape also. Another very good way to use the tape system is as a "RUNNING LOG", where a whole side of a cassette is used to save a developing program, stage-by-stage. If you crash your program, you can re-load it back from tape. A good idea here is to use the high byte of the file number as the program identification and the low byte as the progressive count or version number on the tape. When you have a final version, then save that on a permanent cassette. The "RUNNING LOG" cassette can then be used over and over. Once again, paper work is very important. Make sure you document any differences between successive files. This may help later in de-bugging. Also, always include the date and time as this will give a chronological order to your work.  If you are wondering how many times you should save a file, and at what speed, the answer really depends on the reliability of your system. The major factors in reliability are your tape player and cassette quality and how well you constructed your interface. If any of these are borderline, the system may work but you may have a higher than normal failure rate. Our tests show reliability at better than 98% on saves of 2K blocks. Different cassettes and players were used over many months and rarely did a fault creep in. You can test your system out by saving the monitor 10 times on each speed and then perform a BLOCK TEST. You should get at the very least, 17 out of 20 passes. If not, some trouble-shooting may be required. If you get 19 or 20 you could probably get away with high speed saves and not have to worry about checking them on your running log. For permanent storage, a good system is a high speed save, then two low speed saves and check each afterwards. The low speed save should be more reliable than the high speed save as the low speed save will tolerate the occasional hiccup. However, this extra reliability does not cover all possible causes of failure, e.g. problems related to frequency or bandwidth restrictions of your tape player as the period is not changed only the ratio of pulses. Finally, a file that is absolutely necessary to be retrieved from tape must be stored on two tapes. This provides a double back-up facility against accidental erasure or damage. 

"OH NO!" IT DOESN'T WORK. 

If your tape system fails to work correctly, then check the interface board or better still, have a friend check it. Eliminate any problem and re-try. If problems still exist, test the cassette player with a normal pre-taped audio tape. The music should sound normal and not flutter. If it flutters, the tape player is due for a service or replacement, or if battery operated, the batteries may be flat. Various sections may be eliminated by listening to the tape signal. If the signal saved on the tape sounds ok when played back on the player, but is not heard on the TEC, check the input section of the interface board and also the "E" output of the player with a pair of Walkman-type headphones. It is possible that the volume output is not high enough to be amplified on the interface board. This is very unlikely though on ordinary tape players but we found this to be the case with our VZ-200 data cassette player. If no signal is getting to the TEC and everything else seems to be ok, test the input buffer by setting the tape software to load and taking the input high and low with a jumper lead. The LED on the speaker should echo the inverse of the input. If not, shift the jumper to the collector lead of the input transistor and repeat the process. If the speaker LED now toggles, the input transistor is faulty. If not, investigate the latch chip. Make sure all the pins are well soldered and the feed-throughs are connecting properly. If the tape signal is heard, in the TEC speaker, but the file number is not recognised, loaded correctly, or the tape fails to load the data blocks consistently, try a better quality cassette tape. If problems persist, try a different player as the signal may be distorted or not have enough amplitude. If you still can't get it to go, a repair service is available for $9.00 plus $2.50 postage. 


## THE DAT BOARD

The Display And Tape Board • by Jim 

![](https://github.com/SteveJustin1963/tec-DAT/blob/master/schem.png)

PARTS LIST
* 1 - 100R
* 1 - 470R
* 4 - 10k
* 1 - 10k mini trimpot
* 1 - 100p ceramic
* 2 - 10n greencaps
* 3 - 100n greencaps
* 1 - BC 547
* 1 - 74LS373
* 1 - 74LS74
* 1 - 5mm LED (for trimpot handle)
* 2 - 3.5mm sockets
* 1 - 20 pin IC socket
* 2 - 14 pin sockets (one to cut-up)
* 1 - 20cm 12 way ribbon cable
* 1 - 50cm figure-8 shielded cable
* 1 - 1.2 metres hook-up wire
* 4 - 3.5mm mono plugs
* 1 - 100cm tinned copper wire
* 1 - Female matrix connector
* 3 - 32mm x 2.5mm bolts
* 9 - 2.5mm nuts
* 1 - 16 character x 2 line LCD*
* 1 - DAT PC Board
* Don't Forget: The LCD display can be bought separately

This board will change the way you program for ever. The DAT BOARD is perhaps the most vital addition to the TEC ever. Not just a part time "add on," but rather a permanent addition to your TEC. Once you start using it, we think you'll agree. The name "DAT" is an acronym for Display And Tape. While others brawl over "their" DAT, (have you seen one?), we have quietly slipped in the back door with our version. The DAT BOARD provides these functions: 

* 16x2 LCD display. 
* Cassette tape I/O interface.
* Single stepper module.
* 5 Buffered and latched input bits.
* 1 Inverter for general use.
* Diode clipped input line. (For RS232 input)
* MON select switch.

PORT 3

Port 3 addresses an input latch. Below is a break-down of the bits on port 3.

BIT#
* 0 - Serial in
* 1 - input 1 
* 2 input 4
* 3 - input 2
* 4 input 5
* 5 input 3

The above are the inputs from the 74C14.

* 6 - key pressed signal.
* 7 - Tape input.

CONNECTION

Up until now, TEC add-on's have been connected via the expansion port. We wished to avoid this as there are too many devices cluttering up this area already. The search was on for a better place to put our new board. We decided upon the blank area left of the eprom, because it is common to all TEC's and has up until now not been used by anything else. But there's nothing to connect to there! I hear you say. Well not quite, Simply solder a cut-up I.C. socket onto the links and you have an (almost) instant data buss socket. The DAT BOARD has a set of feed downs that push into the sockets and serve the dual purposes of connection and fixation. 

The feed downs are simply lengths of stiff wire soldered to the underside of the P.C. that extend about 1 to 1.5 cm down to push into the I.C. sockets. The fixing of the DAT BOARD is also aided by three "stand offs," in the form of three bolts with nuts to tighten against the board. These may extend through the TEC board if you want as there is no track work underneath.

CONSTRUCTING THE DAT BOARD

Originally, the kit of parts for the DAT BOARD was going to be supplied in two sections. We have changed our minds since, but have decided to present these construction notes unchanged. The first thing to do, is to fit ALL the links,regardless of what section you are constructing. If you have already built the TAPE and keyboard section and/or are now constructing the LCD/SINGLE STEPPER interfaces then skip ahead to the respective notes. Once you have built the LCD section skip back to the notes on inserting the feed downs, stand-offs and control buss leads. 

THE TAPE AND LATCH SECTION
Most the components for the TAPE SECTION are fitted on the bottom left corner of the board. The exceptions being a 100n greencap, that goes on the middle left of the board, the latch chip and its socket. Fit these in the order you prefer and then solder a short piece of tinned copper wire in the hole marked "SP." This is where the female matrix connector will slide on. If you are wondering why we recommend a piece of tinned wire instead of a male matrix pin, the reason is that the force needed to push a female over a male matrix pin is far to great to be healthy for the TEC or DAT PCBs. (The keyboard is destructive enough). The tinned wire can be tinned again to give just the right fitting diameter, if required. After fitting all the components, cut the length of hook-up wire into 4 equal sections. Strip and tin each end of all the lengths. Solder two pieces to the ground strip next to the tape in and tape out pads on the DAT BOARD. The other ends of these wires solder to the top tags of the 3.5mm sockets. Solder the two remaining wires to the tape in and tape out pads. The other ends are soldered to the DIAGONALLY OPPOSITE tags on the 3.5mm sockets. Keep track of which socket the wires are joined to, and mark them accordingly Drill two holes large enough for the 3.5nun sockets in the back or side of the RETEX case and fit the sockets in place. Strip the ends of the shielded cable and twist the shield into one strand. Remove the covers of the 3.5mm plugs and slide them onto the figure 8 cables, so they are back to back. Solder the shields to the larger tags on the plugs. The middle conductor is soldered to the smaller tags. Do this for each of the four ends. Solder a 5cm piece of hook-up wire on the 1K resistor which connects the output latch to the speaker transistor. The wire is soldered on the LATCH SIDE of the resistor. The other end of the wire is soldered to the female matrix connector. This matrix connector slides over the pin marked SP on the DAT BOARD. Now you are ready to insert the feed downs.

INSERTING THE FEED DOWNS

The feed down are made of stiff tinned wire of about 2cm length. The easiest way to solder these is to solder a continuous length in each hole, and then trim it down afterwards. Do this for all the feed downs and try to get them straight as possible. The feed downs plug in to a cut-up IC socket soldered across the links near the EPROM. The socket is soldered where the links form a straight line as they disappear into the TEC PCB. (See diagram). If you want, you may make the feed downs longer, remove the links, and permanently solder the DAT BOARD in place. Of course, you will need to put jumpers beneath the board to replace the missing links. This arrangement will provide a far more reliable circuit connection. Make sure you have finished the board COMPLETELY before you do this, as you will not be able to solder underneath the board afterwards. 

CONNECTION OF THE CONTROL LINES 

There are 10 control lines that are soldered to the bottom of the TEC board. A 20 cm 12 way ribbon cable is used to make all the connections. The ribbon cable is soldered to a row of pads on the DAT BOARD about 2.5cm  below the top edge. The ribbon cable is
soldered to the BOTTOM SIDE of the DAT BOARD and then drops down between the TEC board and the RETEX case (if you have one). All the connections to the DAT BOARD are printed on the solder side of the board while the connections to the TEC are made as per the wiring diagram. The two 3.5 mm sockets for the tape in/out are mounted in either the back or side of the RETEX CASE. If you do not have a case, then the sockets can be connected with short pieces of wire and left "floating." We do not recommend that you drill holes in either the TEC or DAT boards for the sockets. This is to save the expensive TEC board from the excessive force involved in plugging and unplugging the leads. The best idea is to hold the sockets when inserting the leads. THE STAND-OFFs In addition to the feed downs, three bolts act as stand-offs. The head of these bolts sits on the TEC board or, if you wish, you may drill into the board and feed the bolts up through the board. If you have the original TEC-1 board with the 8212 latch chips, the top bolt will not be able to be feed through the board as there is track work associated with the (now aborted) on-board tape interface and battery backed RAM. If you have drilled the holes, then feed the bolts up from the bottom of the TEC and lock each in place with a nut. A second nut is screwed down to about 1 cm off the TEC board on each bolt. This sets the height of the DAT BOARD. The DAT BOARD is then placed over the two bolts and a third nut is tightened onto the DAT BOARD. If you to not wish to drill into your TEC, which is quite understandable, then place a nut on each bolt and wind it down to about lcm from the head. Poke the bolts through the the hole in the DAT BOARD and tighten down the second nut.
Next, insert the board and note how high it is off the TEC. Ideally it should be 1.5 to 2cm off the board. Trim the feed downs until you are happy with the height. Adjust the stand-offs until they all sit neatly on the TEC board. Finally, a blob of blu-tack can be used to secure the top stand-off on to the board. This will help keep the DAT BOARD square on the TEC. 

TESTING THE LATCH/TAPE INTERFACE

The latch is easily tested by running up JMON. If the keyboard works then the latch is obviously working. You can test each bit of the latch by taking the remaining inputs to ground. These pins are connected to pins 2,4,6,8 and 12 on the 74C14 socket and also pin 3 of the latch chip itself. Make sure that you don't have the 74C14 fitted as this may damage the chip. The following program will echo the latch on the LED display: 

0900 3E 3F D3 02 DB 03 E6 3F
0908 D3 01 C3 00 09

To test the tape, refer to the pages on using the tape system that show how to use and trouble shoot the tape interface. 

THE SINGLE STEPPER/LCD INTERFACES

If you are constructing this section before the tape/latch section, you will need to make a modification to the TEC. The mod is to add a 4k7 resistor between pin 15 of the 4049 and pin 10 of the Z80. The purpose of this mod is to route the DATA AVAILABLE SIGNAL to the DATA BUSS. Without this, JMON is unable to read the keyboard. (This mod is described numerous times throughout this issue). The LCD interface consists of just four components. They are a D flip flop, a 100p cap, a 100R resistor and a 10k trimpot. The D flip flop, (that was
spare) is configured to act as an INVERTER!! This design saved us from having to use another chip. The single stepper interface simply uses one half of a dual D flip flop! 

CONSTRUCTION NOTES 

These 2 interfaces are simple to construct. Just take care with the orientation of the 74LS74 chip. If you have a spare LED on hand then you can solder it onto the trimpot to use as a knob (one is provided in the kit). FITTING THE LCD Place the LCD FACE DOWN on the work bench and feed a 5cm length of tinned copper wire into each hole on the LCD. Solder the wires in place and then, starting at one end, trim the wires to form a ramp. This helps you to insert the 14 wires one-at-a-time into the DAT BOARD. The DAT BOARD edge connector is placed at the top of the DAT BOARD and the LCD overhangs the board like a verandah. Insert the LCD into the DAT BOARD as best you can. A second person with a pair of tweezers could help tremendously in getting each wire down its hole. After you have fitted the wires into their holes, position the LCD to the height you want. This should be about 1 cm to 1.5cm, and carefully solder it in place. 

TESTING THE LCD

After you have finished construction and wired the DAT BOARD to the TEC as shown in the wiring diagram, you're ready to go. Fit the board in place and turn the 10k trimpot clockwise when looking at it from the left. Turn it as far as it goes, then turn it back just slightly. This sets the contrast level and if it is not approximately at the position described above, nothing will appear on the LCD. If you have JMON then fit it into the EPROM socket and power up the TEC. 

All things being equal, the display will show the following:

0900>xx xx xx xx
Data xx xx xx xx

If not, the most likely cause is that one of the data lines is not getting to the display. The easiest way to check this is to type in the following: 

0900 3E 55 D3 04 C7 

AFTER you have entered this, connect a jumper between port 4 and the wait line of the Z80. When you have done this, hit go. The TEC should go "dead." Now, with a logic probe, test the edge connector of the LCD. Starting from the right, the logic levels should be: 

H, L, H, L, H, L, H AND L.

If not, then check all the connections and retry until right. If the connections are right, but there is nothing on the display, check the voltage on pin three of the LCD. This voltage should be in the range of 0.5v to 1 v. Adjust the trimpot until you measure this voltage. Still no luck? Turn off the TEC, hold reset down and turn the TEC back on while still holding down the reset. The top row of the LCD should be dark and the bottom line should be light. If not then there maybe no power getting to the LCD, the contrast voltage may be incorrect (but you have already checked this), or the display has been damaged, they are all tested before they leave 'TE). If the top line is dark when power is applied but the display does not respond when reset is released, then put your logic probe on pin 6 of the LCD. Hold down the "+" key and watch the logic probe. Pin three should pulse HIGH each time the TEC beeps. If not then check that you have the wire going to port 4 in the correct place. Check the track work around the 74LS74 chip and the chip itself. If pin 6 seems ok, then check that the 100p cap is fitted as this is VERY IMPORTANT. Pin 5, the r/w line, should always be pulsing. Check this with the
logic probe. The only other line left to test is the register select (RS). This line is address 7, and the easiest way to check this is with a continuity tester. If the LCD clears when power is applied, but nothing appears on the LCD, then it is oddson that the cause is address 7 not being wired correctly. 

TESTING THE SINGLE STEPPER
This is easy. With JMON fitted, enter this at 0900: 

0900: 00 00 00 00 00 C3 00 09 

Now, press shift 2. The single stepper will show 0900 PC. Press any data key and the single stepper will cycle automatically. The occasional clicking you (may) hear is a result of the interaction of the interrupt response cycle and the decoding of the 74LS138 decoder chip. If the single stepper doesn't work, then check your wiring as it is doubtful that the 74LS74 chip is faulty 

WHAT THE LCD INTERFACE DOES

The LCD is designed to directly interface to microprocessors. Unfortunately there are two main types of microprocessor buss timing and the LCD is designed for the wrong type (as far as we are concerned). In order to get the LCD to interface to the Z80, a little bit of juggling with the tuning is needed. The first problem is the the LCD requires an active HIGH Enable signal. This has been achieved by inverting the PORT 4 I/O select line. This inverting is done by the spare D flip flop on the DAT BOARD. By looking at the TRUTH TABLE for the 74LS74, I found that it was possible to configure it as an inverter if I used the CLR pin as the DATA input! To cut a long story short, the idea worked. Eureka! The next problem is the LCD requires R/W to be stable on the falling edge of the E signal. If you look at the Z80 timing, you will see that the R/W line and the IORQ change state simultaneously. By the time that IORQ has gated port 4 and the port 4 signal has been inverted, the R/VV.line will actual ly change (slightly) before the E line on the LCD! To overcome this problem, a simple RC network has been placed on the R/W line. This RC delay holds the R/W line stable while the E line goes low. The time we are talking about here is just a fraction of a microsecond, but that is all it takes for the chips in the LCD to accept or reject the in-coming signals. Another problem is that the LCD requires 2 ports to communicate with the Z80. It also wants to decode the second port itself. This is a common requirement of many peripheral devices, and the solution provided here is also useful for all these. To give the LCD its second port, and let it decode it for itself, address line 7 has been presented to the LCD. This means that the second port is decoded (by the LCD) on port 84. 

DISPLAY CONTRAST

The LCD requires an external voltage to set the contrast level. The contrast of LCDs varies with temperature and viewing angle. To allow for this, the LCD has an external contrast control. The contrast is controlled by adjusting the voltage on this pin.  This is the function of the 10k trimpot, that is wired as a voltage divider. 

OPTIONS 

Several optional extras can be added to the DAT BOARD. Below is a description of each: 

MON SELECT SWITCH 

When you add the DAT BOARD, there may not be enough room between the board and the EPROM to fit your MON select switch. If this is the case, provision has been made to fit the switch to the DAT BOARD. Simply install the dotted link and move your switch to the dotted switch position on the DAT BOARD. Run a wire between the pin marked 'ROM P21' and pin 21 of the EPROM. 

SERIAL INPUT

The SERIAL INPUT (SI) This input is for a serial signal, or a RS232 level signal from a printer or RS232 device. This input clips the signal, which can be +/-15V to +/-25V, to safe logic levels. This signal winds up as DO on the 74LS373. 

THE 74C14

This has been added to increase the versatility of the DAT BOARD. Some possibilities for it include a touch sensitive qwerty key pad, an external time reference, a thermistor controlled oscillator for temperature measurement or just buffered inputs. Nothing permanent has been planned for it, it is mainly for experimentation. We are open to your ideas! 

THE DIRECT CONNECT PIN

This is located between the transistor and the 6 x 1M resistors. The purpose of this pin is to allow direct connection between two TECs. One TEC can down load to another through the tape software or a serial communication program. (I have a 9600 Baud routine that also talks to IBM's and compatibles). 

THE UNUSED INVERTER 

The input for the unused inverter is the right most matrix pin on the bottom right-hand side of the DAT BOARD. The output is the matrix pin directly above it. 

HOW THE TAPE CIRCUIT WORKS

There's not much to describe about the tape circuit as all the hard work is done by software. The output section consists basically of an AC coupled LOW PASS filter with some attenuation on the end to prevent the digital level voltage from over driving the cassette players input. The input section is just a simple AC coupled common emitter transistor amplifier with the base heavily biased on. The bias on the transistor is important as this ensures that the software is able to read a steady logic 0 when no (AC) input is present. 

HOW THE SINGLE STEPPER INTERFACE WORKS

The single stepper INTERFACE works by interrupting the Z80 after each instruction. The interrupts are generated from a D flip flop on the DAT BOARD. Each time the Z80 fetches the first byte of an instruction a special signal called Ml is generated. This Ml is used to clock the ROM CS line into the D flip flop. The Q-bar output of the flip flop is connected to the IN'Terrupt pin. This means that an interrupt will be requested on every instruction fetch unless the instruction was fetched from the MONitor ROM. It is important to prevent interrupts while executing in the MONitor ROM. If we don't, then an interrupt will occur just after it is re-enabled, at the end of the stepper routine. Immediately following the El (enable interrupt), is a RETum. If an interrupt occurs on this RETum, then the stepper routine is reinvoked and each time this RETum is reached, the program loops back to the stepper routine forever!! (If it wasn't for this problem we would not require any external hardware at all). 

