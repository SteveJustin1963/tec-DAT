```

'
'
'***********************************************************************************
'*                                                                                 *
'*                             LC2D - Version 2                                    *
'*                       Graphics Library for 2x16 LCD                             *
'*                      with Demonstration User Program                            *
'*                        Microchip Pic 16F628 @ 8MHz                              *
'*                              (c) Art 2013                                       *
'*                                                                                 *
'*                          bushprogrammer@gmail.com                               *
'*                                                                                 *
'***********************************************************************************
'
'
DEFINE OSC 4					' but we are really using 8 MHz
DEFINE NO_CLRWDT				' watchdog is cleared manually
LCD_DATAUS CON 50				' LCD timing
LCD_COMMANDUS CON 2000				'
'
DATA  142,145,145,143,129,130,140,128		'9 digit roll stored horizontal
DATA  142,145,147,149,153,145,142,128		'0
DATA  132,140,132,132,132,132,142,128		'1
DATA  142,145,129,130,132,136,159,128		'2
DATA  159,130,132,130,129,145,142,128		'3
DATA  130,134,138,146,159,130,130,128		'4
DATA  159,144,158,129,129,145,142,128		'5
DATA  134,136,144,158,145,145,142,128		'6
DATA  159,129,130,132,136,136,136,128		'7
DATA  142,145,145,142,145,145,142,128		'8
DATA  142,145,145,143,129,130,140,128		'9
DATA  142,145,147,149,153,145,142,128		'0
'
DATA %01110000 ' invader frame a
DATA %00011000 ' stored vertical
DATA %01111101 '
DATA %10110110 '
DATA %10111100 '
DATA %00111100 '
DATA %10111100 '
DATA %10110110 '
DATA %01111101 '
DATA %00011000 '
DATA %01110000 '
DATA %10011100 ' invader frame b
DATA %10011000 ' stored vertical
DATA %01111101 '
DATA %00110110 '
DATA %00111100 '
DATA %00111100 '
DATA %00111100 '
DATA %00110110 '
DATA %01111101 '
DATA %10011000 '
DATA %10011100 '
'
DATA  "  Art 2013" ' LC2D V2 - (c) Brek Martin 2013
'
'''''''''''''''''''''''''''''''''''''''''''''''''''''
'     DO NOT DECLARE ANY OF YOUR VARIABLES HERE!    '
'    PRIVATE PROPERTY - KEEP OUT OF MY CODESPACE!   '
'''''''''''''''''''''''''''''''''''''''''''''''''''''
dis var byte [51]				    ' monochrome display buffer 24x17
rolls var byte [8]				    ' LCD RAM buffers
rolls0 var rolls[0] : rolls1 var rolls[1]	    '
rolls2 var rolls[2] : rolls3 var rolls[3]	    '
rolls4 var rolls[4] : rolls5 var rolls[5]	    '
rolls6 var rolls[6] : rolls7 var rolls[7]	    '
L0 var byte					    ' LCD RAM index and used as counter
CW var byte : CL var byte			    ' multi purpose counters
lind var byte : pind var byte			    ' framebuffer indexing variables
slug var byte : invert var byte			    ' set invert 0xFF to invert display
wtemp var word					    '
temp var wtemp.byte0				    '
tempb var wtemp.byte1				    '
px var byte	: py var byte			    ' coordinates for library routines
'''''''''''''''''''''''''''''''''''''''''''''''''''''
'         END OF DISPLAY BUFFER CODESPACE           '
'''''''''''''''''''''''''''''''''''''''''''''''''''''
'
x var byte	' user coordinates for 2D graphics
y var byte	' these are for the user program
'
dy var byte	' line drawing variables can
y1 var byte	' be removed if not using lines
y0 var byte	' line drawing may break if start
dx var byte	' and end points are the same
x1 var byte	' which is not yet tested
x0 var byte	' thanks to oogabooga to for
stepx var byte	' optimisation of my code for
stepy var byte	' PBP unsigned integer bytes
frac var byte	' expand to words for bigger LCD
'
ftick var byte	' frame count variables can
frame var byte	' be removed if not counting
'
dval var byte	' value for printed variable
digit var byte	' buffer for printing sprites
index var byte	' eeprom index for sprite data
dgx var byte	' coordinates to print sprite
dgy var byte	'
demd var byte	' actual digits on the screen
demdl var byte	'
dfc var byte	' digit frame counter
'
'	circle drawing variables can be removed
'	if you remove the circle drawing routine
'   	some variables are shared with square drawing
'	this circle routine is borrowed from the GLCD
'	library posted by Dave on MELabs PBP forum
'	do not draw circles with radius less than 3.
'
cx var byte	' shared with square drawing routine
cy var byte	'
glc_x var byte	'
glc_y var byte	'
glc_s var word	' slope
radius var byte	' radius
'
cdx var byte	' circle demo horizontal coordinate
'
doff var byte	' digit odometer effect variables
doffl var byte	'
doffm var byte	'
dcompl var byte '
dcompm var byte '
ddirl var bit	' digit counting direction variables
ddirm var bit	' not implemented yet - out of memory
'
xdir var bit	' direction variables that can be
ydir var bit	' removed if not running the demo
'
backled var bit ' LED backlight flash status
'
invert = $FF	' 0xFF to invert display colours
'
'
' execution time!
'
CMCON = 7	' set portb to digital
trisb.6 = 0	'set LCD backlight output
'
'the demo program turns on the backlight
'turn it on here if your program does not
'portb.6 = 1'turn on LCD backlight
'
backled = 1	' initially set led backlight on
ftick = 0	' reset demo section counter
frame = 0	' reset frame counters
x = 2		' set intial point coordinates
y = 2		'
cdx = 11	' set initial circle position
dfc = 0		' reset some variables that could
doff = 0	' break things if not initialised
dval = 0	'
demd = 0	'
demdl = 0	'
digit = 0	'
'

'''''''''''''''
'The code above is a simple demo program that displays a moving point on the LCD screen. 
' The point is controlled by the variables x and y, which are decremented or 'incremented each time through the main loop. 
' The direction of the point is controlled by the variables xdir and ydir, which are set to 0 or 1 depending on the position 'of the point. 
' The demo also includes a function that draws the rest of the ball around the moving point. 
' This is done by drawing four additional pixels at the coordinates (x+1, y), '(x-1, y), (x, y+1), and (x, y-1). 
' The code is written in such a way that it can be easily modified to display different patterns on the screen. 
' For example, the point could be made to move in a spiral 'pattern by changing the values of x and y.
''''''''''''''''''

```
```

PAUSE 1200	'pause for LCD to start
LCDOUT $FE,1	'clear LCD
'
'
cycle:		' main routine - demo user program
@ clrwdt	; clear watchdog timer manually
'
x = x - 1		' move the point for the demo
IF xdir = 0 THEN	' the moving point controlls
x = x + 2		' most of the demo parts
ENDIF
y = y - 1
IF ydir = 0 THEN
y = y + 2
ENDIF
'
IF (ftick < 4 && ftick != 1) THEN ' draw the moving point
px = x+0 : py = y+0 ' draw point
gosub setpixel
ENDIF
'
IF ftick = 0 THEN 	' draw rest of the ball around moving point
px = x+1 : py = y+0	' this is the first demo part
gosub setpixel
px = x-1 : py = y+0
gosub setpixel
px = x+0 : py = y+1
gosub setpixel
px = x+0 : py = y-1
gosub setpixel
ENDIF
'
''''''
' The code checks the screen bounds for the point we are moving around. If the point is outside the bounds, the code changes the direction.

IF (x > 21 && xdir = 0) THEN ' check the screen bounds
xdir = 1		     ' for the point we are moving around
ENDIF
IF (x < 1 && xdir = 1) THEN
xdir = 0
ENDIF
IF (y > 15 && ydir = 0) THEN
ydir = 1
ENDIF
IF (y < 1 && ydir = 1) THEN
ydir = 0
ENDIF
''''''''''''''''''''''''''''''''''
if ftick = 1 THEN 	' draw dynamic circles
cx = x : cy  = y	' this is the second demo part
radius = (y/2) + 2
gosub  drawcircle
ENDIF
'
IF (ftick = 2) THEN 	' draw dynamic lines
x0 = 0 : y0 = 0		' which is an example of diagonal lines
x1 = x : y1 = y
gosub drawline
x0 = x : y0 = y
x1 = 22 : y1 = 0
gosub drawline
x0 = x : y0 = y
x1 = 22 : y1 = 16
gosub drawline
x0 = 0 : y0 = 16
x1 = x : y1 = y
gosub drawline
ENDIF
'
IF ftick = 3 THEN	' draw the crosshair effect
x0 = x : y0 = 0		' which is an example of straight lines
x1 = x : y1 = 16
gosub drawline
x0 = 0 : y0 = y
x1 = 22 : y1 = y
gosub drawline
ENDIF
'
IF (ftick = 4) THEN 	' draw digits
dval = demd /10		' which is an example of drawing sprites
demdl = demd		' where the data was stored horizontal
demdl = demdl - (dval * 10)
dgx = x-6 : dgy = y-4
gosub printdigit
dval = demdl
dgx = x+1 : dgy = y-4
gosub printdigit
ENDIF
'
IF ftick = 5 THEN	' squares
x0 = 11 : y0 = 8
radius = dfc
gosub drawsquare
ENDIF
'
IF ftick = 6 THEN	' squares with strobe
radius = dfc		' coords were set in previous section
gosub drawsquare
ENDIF
'
IF ftick = 7 THEN	' more squares
x0 = x : y0 = y
radius = 5
gosub drawsquare
ENDIF
'
IF ftick = 8 THEN	' dynamic squares
x0 = x : y0 = y
radius = y/2
gosub drawsquare
ENDIF
'
IF (ftick = 9) THEN	' draw invader sprite
dgx = x-5 : dgy = y-4	' which is an example of animated sprite
gosub printsprite	' where the data was stored vertically
ENDIF
'
IF ftick = 10 THEN	' circles trick
cx = cdx : cy  = 8	' a trick to look like the entire LCD is used
radius = 7
gosub  drawcircle
cx = cdx + 24
gosub  drawcircle
cdx = cdx - 1
ENDIF
'
IF ftick == 11 || ftick == 12 THEN	' dynamic circles trick with strobe
cx = cdx : cy  = 8		' a trick to look like the entire LCD is used
radius = (y/2) + 2		'
IF ftick = 12 THEN
cy = 15 - y
ENDIF
gosub  drawcircle
cx = cdx + 24
gosub  drawcircle
cdx = cdx - 1
ENDIF
'
IF ftick = 13 THEN	' rolling odometer effect display
dval = demd /10		' the odometer display also moves
demdl = demd		' around the display
demdl = demdl - (dval * 10)
IF dval != dcompm THEN
'ddirm = 0		' determine digit count direction
'IF dval < dcompm THEN	' odometer only works on a variable
'ddirm = 1		' that is being incremented by one
'ENDIF			' not enough memory to reverse
dcompm = dval
doffm = 8
ENDIF
doff = doffm
IF doffm > 0 THEN
doffm = doffm - 1
ENDIF
dgx = x-6 : dgy = y-4
gosub printdigit
IF demdl != dcompl THEN
'ddirl = 0		' determine digit count direction
'IF demdl < dcompl THEN	' oops, ran out of memory to reverse
'ddirl = 1		' the roll direction of movement
'ENDIF			' so this is incomplete
dcompl = demdl
doffl = 8
ENDIF
doff = doffl
IF doffl > 0 THEN
doffl = doffl - 1
ENDIF
dval = demdl
dgx = x+1 : dgy = y-4
gosub printdigit
ENDIF
'
IF ftick == 14 THEN ' dynamic squares trick
x0 = cdx : y0  = 8  ' a trick to look like the entire LCD is used
radius = (y/2) + 2  '
gosub  drawsquare
x0 = cdx + 24
gosub  drawsquare
cdx = cdx - 1
ENDIF
'
IF cdx = 242 THEN	' check bounds for moving circle demos
cdx = 10		'
ENDIF			'
'
IF ftick = 15 THEN	' reset demo section counter
ftick = 0		' there are currently fifteen demo parts
doff = 0
ENDIF	
'
'
gosub writecg		' write the frame buffer to LCD
'
'
frame = frame + 1	' count actual frames
IF frame = 150 THEN	'
frame = 0		'
ftick = ftick + 1	' frame counter increments demo counter
invert = $00		' revert to normal after first section
ENDIF
'
dfc = dfc + 1		' increment the dynamic squares width
IF dfc > 8 THEN		'
dfc = 0			'
demd = demd + 1		' increment counter for display variable
ENDIF			'
IF demd > 99 THEN	' keep display variable in two digit range
demd = 0		'
ENDIF			'
'
IF ftick = 4 || ftick = 9 || ftick = 13 THEN	' variable sprite delay
PAUSE ftick*20					' for all digit and invader sprites
ENDIF						' otherwise lcd lag messes up the display
'
portb.6 = 1					' strobe the LED backlight
IF ftick = 6 || ftick = 11 THEN			' for these demo sections only
backled = backled + 1				' alternate backlight status
portb.6 = backled				' set led backlight to current status
ENDIF						'
'
goto cycle					' end main routine - do the next frame
'
'
'
'''''''''''''''''''''
' The code above sets a pixel at position (px, py) on a display with a resolution of 50x50 pixels. 
' The variable 'lind' holds the byte index for the line that the pixel is on. 
' The variable 'pind' holds the byte index for the pixel within that line. The variable 'slug' holds the bit index for the pixel within that byte. 
' If the pixel is on the first byte of the line, 'pind' will be 0. If the pixel is on the second byte of the line, 'pind' will be 1. 
' If the pixel is on the third byte of 'the line, 'pind' will be 2. 
' If the pixel is on the first bit of the byte, 'slug' will be 0. If the pixel is on the second bit of the byte, 'slug' will be 1. 
' If the pixel is on the third bit of 'the byte, 'slug' will be 2. 
' The code then sets the appropriate bit in the byte at index 'lind+pind' to 1.
'
'
setpixel:	  ' size and performance win for V2
lind = py * 3 ' byte index for line
pind = 0
slug = px
IF px > 7 THEN
pind = 1
slug = px - 8
ENDIF
IF px > 15 THEN
pind = pind + 1
slug = px - 16
ENDIF
IF lind+pind < 51 THEN ' range check
temp = dis[lind+pind]
FOR CW = 0 TO 7
IF slug = CW THEN
temp.bit7 = 1
ENDIF
wtemp = wtemp << 1
NEXT CW
dis[lind+pind] = tempb
ENDIF
return
'''''''''''''''''''''''''''''''''''''''''''''''''''
'This code is responsible for writing to the LCD screen. It starts by writing the first half of the display, 
' then skipping the invisible lines, and writing the second half of the display. Finally, it draws the first and second lines of the display.
' The code above is used to write to the LCD.
' First, the code sets up the variables needed to write to the LCD. Next, the code writes the first half of the display.
' Then, the code skips the invisible line.
' After that, the code writes the second half of the display.
' Finally, the code draws to the LCD.
'''


writecg:	' size, ram and performance win for V2
L0 = $40	' reset lines
FOR CL = 0 TO 7 ' write first half of display
FOR CW = 0 TO 3
rolls[CW] = (dis[0] ^ invert) >> 3
gosub Rotate
NEXT CW
LCDOUT $FE,L0+$00,rolls[0]
LCDOUT $FE,L0+$08,rolls[1]
LCDOUT $FE,L0+$10,rolls[2]
LCDOUT $FE,L0+$18,rolls[3]
L0 = L0 + 1'
NEXT CL
FOR CW = 0 TO 23 ' skip invisible line
gosub RotateDisplay
NEXT CW
L0 = $60	' reset lines
FOR CL = 0 TO 7 ' write second half of display
FOR CW = 0 TO 3
rolls[CW] = (dis[0] ^ invert) >> 3
gosub Rotate
NEXT CW
LCDOUT $FE,L0+$00,rolls[0]
LCDOUT $FE,L0+$08,rolls[1]
LCDOUT $FE,L0+$10,rolls[2]
LCDOUT $FE,L0+$18,rolls[3]
L0 = L0 + 1'
NEXT CL
' draw to LCD
LCDOUT $FE,$80	'draw first line of display
FOR CL = 0 TO 3
LCDOUT 0,1,2,3	'
NEXT CL
LCDOUT $FE,$C0	'draw second line of display
FOR CL = 0 TO 3
LCDOUT 4,5,6,7					'
NEXT CL
return
'


''''''''''''''''''''''''''''''''''''''''''''''
' This code displays a single digit on the screen. The index is set to the position of the digit, 
' and the code loops through each row and column. If the bit is set to 1, the pixel is turned on at the correct position.
' 
printdigit:	' print a single digit to screen
index = dval * 8' set index position for digit
FOR L0 = 0 TO 7
gosub readeep
FOR CL = 0 TO 4
IF digit.bit4 = 1 THEN
px = dgx+CL : py = dgy+L0
gosub setpixel
ENDIF
digit = digit << 1
NEXT CL
index = index + 1
NEXT L0
return
'''''''''''''''''''''''''''''''''''''''''''''''

'''''''''''''''''''''''''''''
' This code prints a monochrome graphic sprite to the screen. The index position for the sprite is set to 88. 
' If the frame's bit 3 is set to 1, then the index position is incremented by 11. The code then loops through 10 lines of the sprite, 
' reading each one and printing it to the screen. For each line, the code loops through 8 columns, checking if each pixel is set to 1. 
' If it is, the code calculates the coordinates of the pixel and calls the setpixel subroutine to print it.
' 
printsprite:	' print a monochrome graphic sprite to screen
index = 88	' set index position for sprite
IF frame.bit3 = 1 THEN ' select frame
index = index + 11
ENDIF
FOR L0 = 0 TO 10
gosub readeep
FOR CL = 0 TO 7
IF digit.bit0 = 1 THEN
py = dgx+CL : px = dgy+L0
gosub setpixel
ENDIF
digit = digit >> 1
NEXT CL
index = index + 1
NEXT L0
return
'

'''''''''''''''''''''
' This code draws a square to the screen. The square is centered at (x0, y0) with a radius of radius.
' The code works by first setting cx and cy to the radius and 0, respectively. 
' It then loops while cx is greater than or equal to cy. Each iteration, it sets the pixel at (px, py) to the color specified by digit, 
' where px = cx + x0 and py = cy + y0. It also sets the pixel at (px, py) to the color specified by digit, 
' where px = cy + x0 and py = cx + y0. Finally, it sets the pixel at (-cx + x0, cy + y0) and the pixel at (-cy + x0, cx + y0) to the color specified by digit.
' After the loop, the code sets the pixel at (x0 - radius, y0), (x0, y0 - radius), (-x0 + radius, y0), and (-x0, y0 + radius) to the color specified by digit.
'
'

readeep:
'READ index+8,digit		' not ever using the rolling odometer effect
READ (index-doff)+8,digit	' are using rolling odometer effect sometimes
return				' slight performance penalty if you are
'
drawsquare:		' draw square to screen
  cx = radius : cy = 0
  WHILE cx >= cy
	px = cx + x0 : py = cy + y0
	gosub setpixel
	px = cy + x0 : py = cx + y0
	gosub setpixel
	px = -cx + x0 : py = cy + y0
	gosub setpixel
    px = -cy + x0 : py = cx + y0
	gosub setpixel
    px = -cx + x0 : py = -cy + y0
	gosub setpixel
    px = -cy + x0 : py = -cx + y0
	gosub setpixel
    px = cx + x0 : py = -cy + y0
	gosub setpixel
    px = cy + x0 : py = -cx + y0
	gosub setpixel
    cy = cy + 1
  WEND
return
'
drawcircle:		' draw circle to screen
  	glc_x = 0
  	glc_y = radius
  	glc_s = 2-2*radius
  	WHILE (glc_x <= glc_y)
	px = glc_x+cx : py=glc_y+cy
	gosub setpixel
	px = cx-glc_x : py=glc_y+cy
	gosub setpixel
	px = cx+glc_x : py=cy-glc_y
	gosub setpixel
	px = cx-glc_x : py=cy-glc_y
	gosub setpixel
	px = glc_y+cx : py=glc_x+cy
	gosub setpixel			
	px = cx-glc_y : py=cy+glc_x
	gosub setpixel
	px = cx+glc_y : py=cy-glc_x
	gosub setpixel
	px = cx-glc_y : py=cy-glc_x
	gosub setpixel
	IF (glc_s.15 =1) THEN
    glc_s = glc_s + (4*glc_x + 6)
    ELSE
    glc_s = glc_s + (4*(glc_x-glc_y) + 10)
    glc_y = glc_y - 1
	ENDIF
	glc_x = glc_x + 1
  	WEND
return
'

''''''''''''''''''''''''''''''''''
' This code draws a line from point (x0,y0) to point (x1,y1) on the screen. It uses the Bresenham line algorithm.
' First, the code calculates the slope of the line, and the direction in which it should be drawn. 
' Then, it calculates the 'fraction' (frac) of the line that has been drawn so far.
' The code then enters a loop, where it draws a pixel at the current position, and then moves to the next position along the line. 
' The loop continues until the end point is reached.
'

drawline:	' draw any line to screen including diagonals
	stepx = 0
	stepy = 0
	frac = 0
	'line from start point x0,y0 to destination point x1,y1.
	dy = y1 - y0
	dx = x1 - x0
	IF dy > 128 THEN
    dy = 0 - dy
    stepy = stepy - 1
    ELSE
    stepy = 1
    ENDIF
	IF dx > 128 THEN
    dx = 0 - dx
    stepx = stepx - 1
    ELSE
    stepx = 1
    ENDIF
	dy = dy << 1
	dx = dx << 1
    'draw pixel
	px = x0 : py = y0
	gosub setpixel
	IF (dx > dy || dx > 128) THEN
    frac = dy - (dx >> 1)
    WHILE x0 != x1
    IF (frac < 128) THEN
	y0 = y0 + stepy
 	frac = frac - dx
	ENDIF
    x0 = x0 + stepx
    frac = frac + dy
    'draw pixel
	px = x0 : py = y0
	gosub setpixel
    WEND
	ELSE
    frac = dx - (dy >> 1)
    WHILE y0 != y1
    IF (frac < 128) THEN 
	x0 = x0 + stepx
	frac = frac - dy
	ENDIF
    y0 = y0 + stepy
    frac = frac + dx
    'draw pixel
	px = x0 : py = y0
	gosub setpixel
    WEND
	ENDIF
return
'

''''''''''''''''''''''''''''''
' The code rotates the display array right by one bit. 
' This is done by first shifting all the bits in the array to the right by one, and then setting the bit at the beginning of the array to 0.
'
'
Rotate:									' the only assembler routine
gosub rota								' needed for speed
rota:									' by neglecting to carry the
gosub RotateDisplay						' status bit, it also clears
gosub RotateDisplay						' the buffer for the next frame
RotateDisplay:							' bitwise rotate array right
  @ rlf 	_dis+50		,F				; ditching the first bit
  @ rlf 	_dis+49		,F				;
  @ rlf		_dis+48		,F				;
  @ rlf		_dis+47		,F				;
  @ rlf		_dis+46		,F				;
  @ rlf		_dis+45		,F				;
  @ rlf		_dis+44		,F				;
  @ rlf		_dis+43		,F				;
  @ rlf		_dis+42		,F				;
  @ rlf		_dis+41		,F				;
  @ rlf		_dis+40		,F				;
  @ rlf		_dis+39		,F				;
  @ rlf		_dis+38		,F				;
  @ rlf		_dis+37		,F				;
  @ rlf		_dis+36		,F				;
  @ rlf		_dis+35		,F				;
  @ rlf		_dis+34		,F				;
  @ rlf		_dis+33		,F				;
  @ rlf		_dis+32		,F				;
  @ rlf		_dis+31		,F				;
  @ rlf		_dis+30		,F				;
  @ rlf		_dis+29		,F				;
  @ rlf		_dis+28		,F				;
  @ rlf		_dis+27		,F				;
  @ rlf		_dis+26		,F				;
  @ rlf		_dis+25		,F				;
  @ rlf		_dis+24		,F				;
  @ rlf		_dis+23		,F				;
  @ rlf		_dis+22		,F				;
  @ rlf		_dis+21		,F				;
  @ rlf		_dis+20		,F				;
  @ rlf		_dis+19		,F				;
  @ rlf		_dis+18		,F				;
  @ rlf		_dis+17		,F				;
  @ rlf		_dis+16		,F				;
  @ rlf		_dis+15		,F				;
  @ rlf		_dis+14		,F				;
  @ rlf		_dis+13		,F				;
  @ rlf		_dis+12		,F				;
  @ rlf		_dis+11		,F				;
  @ rlf		_dis+10		,F				;
  @ rlf		_dis+9		,F				;
  @ rlf		_dis+8		,F				;
  @ rlf		_dis+7		,F				;
  @ rlf		_dis+6		,F				;
  @ rlf		_dis+5		,F				;
  @ rlf		_dis+4		,F				;
  @ rlf		_dis+3		,F				;
  @ rlf		_dis+2		,F				;
  @ rlf		_dis+1		,F				;
  @ rlf		_dis+0		,F				;
  @ bcf		_dis+50		,0				;clear MSB
return
'
'


