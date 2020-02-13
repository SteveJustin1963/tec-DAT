# tec-DAT
A TEC-1 Digital Audio Tape data system and LCD display, for saving or playback of programs and displaying 16x2 ASCII characters.  
By Jim Robertson

## From TE-15

## TEC TALK
SENDING IN PROGRAMS VIA TAPE 

We are looking forward to readers sending programs to us. ... Provide us with a copy of the program. Save it on tape with a crystal speed of half 3.58MHz. ... We also need documentation on the program. Write what it does and where it runs in memory and include any notes you may have generated. The first thing we will do is disassemble it and load it into our IBM clone. Here we can format it for publishing. For the sake of our disassembler, please, if you can, put tables at the end of the program code and write down where the tables are located. This way we can use our HEX dump routine and tack the tables on at the end of the code.

JMON UP-GRADES

JMON has been designed to be upgraded without losing software compatibility. Some likely changes are the removal of the low speed tape save (unless there is a storm of protest). This will decrease the software overhead in the tone routine and even-up the period measurement. The result will be an increase in the tolerance of different TEC frequencies and different tape speeds. This should make it possible to freely interchange half 3.58MHz and half 4.MHz tape software as well as allowing poorer quality tape players to be used. The single stepper, which has no effect on the MONitor at all, may be shifted to a more specialized ROM to increase the stepper's abilities.-
The keyboard and LCD RST's will not be changed, so any routine you write using these will run on future up-grades. The same cannot be said if you directly call into JMON. So don't do it! 

![](https://github.com/SteveJustin1963/tec-DAT/blob/master/dat-15-17.png)
