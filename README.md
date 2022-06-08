# tec-DAT
A TEC-1 D_isplay A_nd T_ape (DAT) data system using LCD display, for saving or loading programs and displaying 16x2 ASCII characters.  
By Jim Robertson. It uses the JMON monitor code in ROM.

- TE-15, pg17, pg47
- https://github.com/SteveJustin1963/tec-MAGAZINES/blob/master/talking_electronics_15.pdf


![](https://github.com/SteveJustin1963/tec-DAT/blob/master/pics/ccxx33.png)
![](https://github.com/SteveJustin1963/tec-DAT/blob/master/pics/ccvv55.png)


## Circuit
https://easyeda.com/editor#id=5436587669434d578bdf98f6c96d4d5b


## Notes on encoding data
DAT is done by encoding digital data using analog signals. This can be done by changing the amplitude, frequency or phase of a periodic repeating wave.

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

s(t) = A cos(2 Pi Fc t)      // digital 1 
s(t) = A cos(2 Pi Fc t + Pi) // digital 0

By adding in Pi we shift this signal to a different phase. We are once again using a carrier frequency but it will be the same frequency for both encoding a binary 0 and a binary 1 now. Because if you remember your trigonometric identities we can actually simplify this a bit further so when we want to encode a binary 0 we simply take the binary 1 signal and negate it and that is effectively the same as shifting the phase by PI. Therfore

s(t) =   A cos(2 Pi Fc t)  // digital 1 
s(t) = - A cos(2 Pi Fc t ) // digital 0

If we use a carrier frequency of 2 the result will look like

![](https://github.com/SteveJustin1963/tec-DAT/blob/master/pics/bpsk.jpg)

There are other methods as well see https://en.wikipedia.org/wiki/Phase-shift_keying

