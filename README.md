# tec-DAT
A TEC-1 Digital Audio Tape data system and LCD display, for saving or playback of programs and displaying 16x2 ASCII characters.  
By Jim Robertson

## From TE-15 


## Chats
Ian McLean? to Australian Vintage Computer Group
January 23
Ben Grimmett's speech board working on my TEC1D with the DAT board and 4MHz crystal.
Note the bodgied BC557, 1K resistor and 10u electro hanging off the side of the board. I needed to add this back in from Craig Hart's original circuit design to switch the op-amp on only when speaking - I was getting a high pitched tone noise on the speech board when idle with the LM386 always on, probably due to old electro's. When the CPU is in Halt (instruction 76) or the LED display is off, the noise would go away. When speaking, the speech board was clear and noise free. Now it always is and working well!

This is the original SPO chip from my old speech board, still working!
==============
Ben Grimmett?Australian Vintage Computer Group
January 11 · 
 
How do you feel about a TEC DAT board which fits into the Z80 Socket - With a Z80 socket on the DAT board? This requires the least number of wires run to various points on the board and also allows room for the EPROM emulator board.

I've also omitted the 5 digital inputs.

Thoughts?
55
20 Comments
1 Share
Like
Comment
Share
Comments
View 2 more comments
Scott Gregory
Scott Gregory That could work. Count me in if you do it.
Hide or report this
Like
 · Reply · 7w
Stuart Remphrey
Stuart Remphrey Not sure if I'd get this "DAT2" or not; but probably, "just in case it's useful"... ;-)
(edit) WANT: so I could try out JMON!…See More
Hide or report this
Like
 · Reply · 6w · Edited
Stuart Remphrey
Stuart Remphrey Hmm, or actually:
Simpler to just socket/replace the cheap latch/buffer chip if(when?!) it blows...
Hide or report this
Like
 · Reply · 6w
Stuart Remphrey
Stuart Remphrey Oh, and Z80-socket-mount is a good idea. Again, simpler.
With that layout, would anything else also fit at the same time? (i.e. expansion socket not blocked?)
1
Hide or report this
Like
 · Reply · 6w
Ian McLean
Ian McLean Looking good Ben! I never used those 5 digital inputs. To be useful for byte input, it had to be used in "nibble mode", with the 5th bit indicating high or low nibble, which is a bit of a pain because it isn't as simple as masking the input from port 3. I would much prefer an 8 way bidirectional port too.
2
Hide or report this
Like
 · Reply · 6w · Edited
David Thornley
David Thornley Brilliant!
Hide or report this
Like
 · Reply · 6w
==========
