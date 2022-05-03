# tec-DAT
A TEC-1 Display And Tape data system using LCD display, for saving or loading programs and displaying 16x2 ASCII characters.  
By Jim Robertson

- TE-15, pg17, pg47
- https://github.com/SteveJustin1963/tec-MAGAZINES/blob/master/talking_electronics_15.pdf


![](https://github.com/SteveJustin1963/tec-DAT/blob/master/pics/ccxx33.png)
![](https://github.com/SteveJustin1963/tec-DAT/blob/master/pics/ccvv55.png)


## Circuit
https://easyeda.com/editor#id=5436587669434d578bdf98f6c96d4d5b


## Notes
DAT is done by encoding digital data using analog signals. This can be done by changing the amplitude, frequency or phase of a periodic repeating wave.

From www;
For example one approach is known as ASK, amplitude shift keying and this approach involves having a way that either has a positive amplitude or an amplitude of zero to encode the bits 1 and 0. 

s(t) = A cos(2 Pi Fc t) // digital 1 then A>0, 0 A=0

The formula over time looks like this so s is the function for the signal voltage that is being transmitted and T is the current time of the transmission and if we are encoding a binary 1 at that time then the signal is some amplitude times cosine of 2 pi times some carrier frequency times the time. otherwise 0 is the voltage of
the signal so we can see what this looks like in the following example.

The delineation of each signal element I'll be encoding this binary string using amplitude shift keying so whenever there is a 0 we simply have a flat line of 0 voltage but whenever there is a 1 we will have some wave with the given amplitude. The number of ripples within a single signal element depends on what the carrier frequency is but it ultimately doesn't matter too much for how ASK works it's just a matter of a technical detail so here when we're encoding ones we have a wave that's fluctuating and then when we go back to 0 we have a flat line again then for the one will have wave again then flat for zero then waving for the one that's throughout here as well and etc.

This is not the only 2:50
way to encode digital data using analog
2:52
signals instead of changing the
2:54
amplitude we could instead change the
2:56
frequency and one scheme for doing this
2:59
is binary frequency shift keying now
3:05
strictly speaking amplitude shift keying
3:07
is also binary and that there are only
3:10
two options the reason that binary shift
3:13
keying explicitly uses the word binary
3:15
here is that there's another scheme
3:16
called multi frequency shift keying
3:19
where we can encode more signals in just
3:22
zeros and ones but if we're only
3:24
encoding zeros and ones we have a
3:26
formula that looks like the following
3:28
this function like the previous one
3:31
encodes the signal as a function of time
3:33
and we still have an amplitude cosine
3:36
and a 2pi the only difference between
3:38
encoding a one or a zero is that the
3:42
frequencies are different we have one
3:45
frequency that we'll use for encoding a
3:46
binary one in a different frequency that
3:49
we'll use for encoding a binary zero if
3:52
we use a frequency of 1 for binary 0 and
3:56
a frequency of 2 for binary 1 we get a
4:00
result that looks like the following
4:01
I'll be using this line paper once again
4:04
to show how this signal gets encoded for
4:07
this bit string so recall that we're
4:10
going to use a frequency of 1 for the
4:12
zeros so when I have a zero I will do a
4:17
single wave like so and I'll repeat that
4:23
for the next zero
4:27
then what I encounter the one I'm going
4:29
to double the frequency and so I'll have
4:32
twice as many peaks and it will look
4:34
like this and we have another one and
4:47
then when we go back to zero we get only
4:50
a single wave in that interval so I can
4:59
carry along and encode this the rest of
5:01
the way and we'll see that for the
5:03
zeroes we have waves that look like
5:05
these and for the ones we have waves
5:08
with higher frequency that look like
5:09
these and so we have this final result
5:12
where we have 0 0 1 1 0 1 0 1 1 1 0 0 1
5:18
0 0 0 1 encoded by changing the
5:22
frequency but for each signal element
5:25
now I mentioned that we are not limited
5:28
to using 2 frequencies we can actually
5:33
create a scheme known as multiple
5:36
frequency shift keying and the formula
5:39
looks like the following
5:40
so this generic formula looks just like
5:43
this one except we've generalized the
5:45
frequency and I've put here that we're
5:47
encoding different values of I but we
5:51
have to pick the values of I and the
5:54
frequency in such a way that we span the
5:57
range of possible values we're encoding
5:58
so I will actually be in a given range
6:02
and we will spread the frequencies out
6:07
within that range to make sure that each
6:10
of them is distinct however as you may
6:14
be able to imagine as the number of
6:16
different frequencies we use increases
6:20
it can be increasingly difficult to
6:22
actually discern the distinction between
6:25
different frequencies so there is a risk
6:31
of having trouble discerning the signal
6:33
that comes with using this approach of
6:37
course the benefit of it is that we can
6:39
encode
6:40
or data per single signal element for
6:44
example rather than simply encoding
6:47
binary values of 0 & 1 we could encode
6:49
values of 0 1 2 & 3 which would
6:53
correspond to binary bits of 0 0 0 1 1 0
6:59
& 1 1 the last encoding method we'll be
7:04
discussing is binary phase-shift keying
7:07
this approach will use essentially the
7:09
same base formula as the others but now
7:13
we will be changing the phase of our
7:14
signal rather than the frequency or the
7:16
amplitude the formula looks like this so
7:21
by adding in this value of pi we shift
7:25
this signal to a different phase we are
7:28
once again using a carrier frequency but
7:31
it will be the same frequency for both
7:33
encoding a binary 0 and a binary 1 now
7:39
I've written these out to the side
7:41
because if you remember your triggermen
7:45
trigonometric identities we can actually
7:47
simplify this a bit further so when we
7:50
want to encode a binary 0 we simply take
7:54
the binary 1 signal and negate it and
7:58
that is effectively the same as shifting
8:01
the phase by PI if we use a carrier
8:06
frequency of 2 the result will look like
8:09
this so we will encode a 0 using the
8:12
shifted phase so this 0 gets encoded
8:16
with a wave that starts on a downward
8:19
path like so
8:31
and then we repeat that with the next
8:33
zero but when we switch to a one the
8:42
phase shift causes the wave to look like
8:46
this and also the next signal
9:01
for the next 0 we shift the phase so we
9:05
reverse directions and then for the one
9:12
we reverse the direction again and if we
9:19
continue this process we'll get the
9:21
following result so you can see in this
9:24
final result that whenever I switch from
9:27
0 to a 1 I get a direction change in the
9:32
wave this sort of sharp change that is
9:36
on the upward end and whenever I go from
9:39
a 1 to a 0 I get a similar sharp change
9:43
but on the bottom end so whenever I'm
9:46
not switching Peaks for a long period
9:51
like here that is a sequence of the same
9:54
element so these 3 encoding schemes here
9:59
represent three relatively
10:01
straightforward means of encoding
10:03
digital data with analog signals they
10:07
take advantage of the primary features
10:09
of a periodic wave we can modify the
10:12
amplitude frequency or the phase

