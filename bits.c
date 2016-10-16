/* 
 * CS:APP Data Lab 
 * 
 * Avery Jones, a13041110
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0


#endif


/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */



/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) 
{
  /* compute AND by flipping the inputs, ORing them together, and flipping
  the result */
  x = ~x;
  y = ~y;
  return ~(x|y);
}

/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56 = 86
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) 
{
  /* shift the desired byte to the LSByte spot and isolate it using AND */
  x = x >> (n<<3);
  return (x & 0xFF);
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) 
{
  /* determine if x is zero, then create a mask to change the possible sign 
  fill into the MSB to be zero/logical */
  int isZero, mask;
  isZero = !(n | 0x0);
  x = x >> n;
  //mask has 1's where the fill bits are, and 0's everywhere else
  mask = (0x1 << (31+isZero)) >> (n + (~0));
  mask = ~mask;
  return (x&mask);
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) 
{
  /* count the number of bits set to 1 by isolating each bit and shifting */
  int a, b, c, d, e;
  a = (0x55 << 8) + 0x55;         // a = 0x55555555
  a = (a << 16) + a;
  
  b = (0x33 << 8) + 0x33;         // b = 0x33333333
  b = (b << 16) + 0x33;
  
  c = (0x0F << 8) + 0x0F;         // c = 0x0F0F0F0F
  c = (c << 16) + 0x0F;
  
  d = (0xFF << 24) + 0xFF;        // d = 0x00FF00FF
  
  e = (0xFF << 8) + 0xFF;         // e = 0x0000FFFF
  
  x = (x & a) + ((x >> 1) & a);
  x = (x & b) + ((x >> 2) & b);
  x = (x & c) + ((x >> 4) & c);
  x = (x & d) + ((x >> 8) & d);
  x = (x & e) + ((x >> 16) & e);
  return x;
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) 
{
  /* computes !x by having a 1 in LSB if its 0, and 0 in the LSB if its not*/
  int notX, negX;
  notX = ~x;
  negX = notX + 1;
  x = (~negX & notX)>>31;
  return x&1;
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) 
{
  /* find the minimum by placing a 1 into the MSB which makes the smallest 
  possible number in 2's complement */
  return ( 0x1 << 31 );
}


/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) 
{
  /* find if an integer can be represented by shifting it back and forth 
  then checking if still equals the original */
  int shift, mask, tempX;
  shift = 33 + ~n;
  mask = x << shift;
  tempX = mask >> shift;
  return !(tempX ^ x);
}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) 
{
  /* divide by a power of 2 by exploiting the fact that shifting right 
  divides by 2 for each bit shifted left, negative numbers have to be 
  positive before the shift */
  //if its negative, perform a 2's complement
  int signBit, mask;
  printf("x: %x\n", x);
  
  signBit = ((1 << 31) & x);
  printf("signBit: %x\n", signBit);
  mask = signBit >> 31;
  printf("mask: %x\n", mask);
  x = (x ^ mask) + signBit;
  printf("x after 2's before shift: %x\n", x);
  //shift right once you have positive number
  x = x >> n;
  printf("x after shift: %x\n", x);
  //if signBit is negative then perform 2's complement again
  x = (x ^ mask) + signBit;
  printf("x after shift and 2's: %x\n", x);
  return x;
}

/* 
 * negate - return -x 
 * You may handle results that fall out of signed int range in any way that you
 * like
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) 
{
  /* negate using the rules for 2's complement (flip bits and add 1)*/
  x = ~x;
  return (x+1);
}

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) 
{
  /* find if the input is positive by isolating the sign bit */
  int isZero, signBit, isPos;
  isZero = !x;
  signBit = ((1 << 31) & x);
  isPos = !(x & (signBit));
  return isPos ^ isZero;
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) 
{
  /*int difference = y + (~x + 1);
  int equal = !difference;
  
  int sign = x^y;
  int out = ~sign;???
  
  signX = sign & x;
  
  difference = ~difference;
  
  
  
  int xSign = x & (0x1 << 31);
  int ySign = y & (0x1 << 31);
  int sign = x^y;
  int difference = y + (~x +1);
  int equal = !difference;*/
  
  return 2;
}

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) 
{
  /* find log of x by finding the location of the leading 1 */
  int a, b, c, d, e;
  
  //gets the leading bit followed by all 1's
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);
  
  // use bitCount logic to count the number of 1's which is the floor(log(x))
  a = (0x55 << 8) + 0x55;         // a = 0x55555555
  a = (a << 16) + a;
  
  b = (0x33 << 8) + 0x33;         // b = 0x33333333
  b = (b << 16) + 0x33;
  
  c = (0x0F << 8) + 0x0F;         // c = 0x0F0F0F0F
  c = (c << 16) + 0x0F;
  
  d = (0xFF << 24) + 0xFF;        // d = 0x00FF00FF
  
  e = (0xFF << 8) + 0xFF;         // e = 0x0000FFFF
  
  x = (x & a) + ((x >> 1) & a);
  x = (x & b) + ((x >> 2) & b);
  x = (x & c) + ((x >> 4) & c);
  x = (x & d) + ((x >> 8) & d);
  x = (x & e) + ((x >> 16) & e);
  return x + ((1<<31)>>31);
}




/*For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. */

/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) 
{
  /* find the negative value of the input by flipping the sign bit of the 
  floating point representation */
  
  int expMask, mantissaMask;
  
  //testing if NaN (all 1's in exponent AND any 1's in the mantissa
  expMask = (0xEF << 25);
  mantissaMask = (0x1 << 23);
  if( ((uf & expMask) == expMask)  &&  ((mantissaMask & uf) != 0) )
      return uf;
  // if it is a number, return the negative
  return ( uf ^ (1 << 31) );
}


/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x)
{
  /* turn an int into a float by creating the sign, exponent, and mantissa 
  segments, then combining them into the new floating point number rep */
  int newFloat, sign, exponent, leadingOneBit, mask, mantissa, mantissaMask;
  
  newFloat = 0;
  
  //check for 0
  if( x == 0 )
      return 0;
  
  //create sign bit, change to positive number if needed
  sign = 0;
  if( x < 0 ) 
  {
      sign = 0x80000000 | newFloat;
      x = ~x + 1;
  }
  
  //create exponent
  exponent = 0;
  leadingOneBit = 31;
  mask = 0x40000000;
  //loop until the first 1 from the MSB is found
  while( !(mask & x) == 1 && leadingOneBit > 1) {
      leadingOneBit --;
      mask = mask >> 1;
  }
  exponent = leadingOneBit - 1;
  exponent = exponent + 127;
  //place exponent in designated 8 bits
  exponent = exponent << 23;
  
  //create mantissa
  mantissa = 0;
  mantissaMask = ~(0x80000000 >> (32-leadingOneBit));
  mantissa = mantissaMask & x;
  mantissa = mantissa << (24-leadingOneBit);
  
  //combine everything
  newFloat = newFloat | sign;
  newFloat = newFloat | exponent;
  newFloat = newFloat | mantissa;
  return newFloat;
}


/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) 
{ 
  /* double the argument by extracting the exponent, adding 1, then 
  replacing the old exponent with the new one */
  
  int expMask, mantissaMask, exp, newExp;
  
  //testing if NaN (all 1's in exponent AND any 1's in the mantissa
  expMask = (0xEF << 25);
  mantissaMask = (0x1 << 23);
  if( ((uf & expMask) == expMask)  &&  ((mantissaMask & uf) != 0) )
      return uf;
      
  //check for 0
  if( uf == 0 )
      return 0;    

  //retrieve the exponent and increment
  exp = 0x7F800000 & uf;
  newExp = exp + 0x00800000;
  uf = uf & 0x803FFFFF;
  return newExp | uf;
}


