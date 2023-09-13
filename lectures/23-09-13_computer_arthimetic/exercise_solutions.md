# Exercise sols 13/09 Jakob Svenningsen

## 3.1

What is 5ED4 − 07A4 when these values represent unsigned 16-bit
hexadecimal numbers? The result should be written in hexadecimal. Show your work

Using same subtraction method as for decimal numbers:\
5ED4\
07A4\
5730

## 3.3 Convert 5ED4 into binary number. What makes base 16 (hex) an attractive numbering system for representing values in a computer?

0101 1110 1101 0100

Hex is attractive as it is a power of 2, making it easy to represent binary numbers. 1 Hex equals 4 bits making the convertion back and fort easy without loss of precision. Also as bytes are 8 bits long this is easy representable with 2 hex. Hex is also easier to read by humans than binary.  


## 3.20 What decimal number does the bit pattern 0X0C000000 represent if it is a twos complement integer? And unsigned integer? (the typesetting is terrible here; what appears to be a multiplication is supposed to read 0X0C000000).

First convert to binary then to decimal.
0000 1100 0000 0000 0000 0000 0000 0000
Unsigned 2^26 + 2^27 = 201326592 
Two's complement = Same as sign bit is 0 (Pos)


Fun Reading, wondering why twos complement works?
Why twos complement work —> https://math.stackexchange.com/questions/1920772/why-twos-complement-works 
https://shorturl.at/EGKZ2


## 3.22 What decimal number does the bit pattern 0X0C000000 represent if it is a floating point number? Use IEEE-754 standard. (the typesetting is terrible here; what appears to be a multiplication is supposed to read 0x0C000000)

0000 1100 0000 0000 0000 0000 0000 0000 (32 bits)
Extract mantissa, exp, sign bit
Sign bit: 0 (Positive)
Exponent: 000 1100 0
Mantissa: 000 0000 0000 0000 0000 0000

So clearly a positive number, +
Mantissa is simply 0. 
Exp, we must account for bias, so E = Exp - bias, i.e. 
000 1100 0 = 24-127 = -103 

Remember representation (−1)^S * M * 2^E ->\
Answer:
* 1 * 0 * 2^(-103)

## 3.23 Write down binary representation of decimal number 63.25 assuming IEEE-754 single precision format.

First we want the number itself converted to binary.
Do integer part first: Also possible to use long division algorithm
111111.01

More systematically, one can use the long division algorithm:
Integer part:

| X   | X/2 | Bit
| -------- | ------- |-----
|  63  |  31   |   1      |
|  31 |    15 |    1     |
|  15 |    7 |     1    |
|   7 |    3 |     1    |
|   3 |     1|     1    |
|   1|     0|      1   |

Fraction part:

| X   | X*2 | Bit
| -------- | ------- |-----
|  0.25  |  0.5   |    0     |
|  0.5     |  1     |  1    |
|   0    |  X=0, stop     |      |
|       |       |      |

Now  we have the binary number, we need it IEEE-754 encoded\
Need to shift binary point left 5 times to normalize\
1.1111101 * 2^-5\
Exp = 5 + 127 = 132 (Because Exp = E + bias)\
Sign bit 0: Number is Pos, encoding becomes\
132 in binary = 0 1000 0100\
Encoding becomes\
0 x 1000 0100 x 1111 1010 000...0


## 3.24 Write down binary representation of decimal number 63.25 assuming IEEE-754 double precision format.
Same as before, but now we have the binary number, we need it IEEE-754 encoded\
Need to shift binary point left 5 times to normalize\
1.1111101 * 2^-5\ (The 1 integer is implicit, remember that!)
Exp = 5 + 1023 = 1028 (Because Exp = E + bias), says 1023 bias for double on slide 33.\
Sign bit 0: Number is Pos, encoding becomes\
1028 in binary = 100 0000 0100
Encoding becomes:\
0 x 100 0000 0100 x 1111 1010 000...0

## 3.27 (Half precision). Write down bit pattern to represent -1,5625 x 10^-1 using excess 16 bits for exponent.

Sign bit: -1 (neg)\
First normalize to 10^0\
In binary (May be converted as shown earlier)\
-0.00101\
Move binary point three times right\
-1.01 * 2^-3\
e = -3\
Exp = -3 + 15 = 12\
12 in binary 1100\
Putting it all together\
1 x 01100 x 010 0000 000
