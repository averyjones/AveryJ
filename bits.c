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
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */


  /*Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:*/
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the gradescope autograder to check for logical correctness 
 */


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
  int z = x|y;
  return ~z;
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
  x = x >> (8*n);
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
  int isZero = !(n | 0x0);
  x = x >> n;
  //mask has 1's where the fill bits are, and 0's everywhere else
  int mask = (0x1 << (31+isZero)) >> (n + (~0));
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
  return 2;
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
  int notX = ~x;
  int negX = notX + 1;
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
  int shift = 33 + ~n;
  int mask = x << shift;
  int tempX = mask >> shift;
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
  /* divide by a power of 2 by exploiting the fact that shifting left 
  divides by 2 for each bit shifter left */
  return (x << n);
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
  int isZero = !x;
  int signBit = ((1 << 31) & x);
  int isPos = !(x & (signBit));
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
  //gets the leading bit by itself
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);
  
  
  
  return 2;
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
  //testing if NaN (all 1's in exponent AND any 1's in the mantissa
  int expMask = (0xEF << 25);
  int mantissaMask = (0x1 << 23);
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
  int newFloat = 0;
  
  //check for 0
  if( x == 0 )
      return 0;
  
  //create sign bit
  int sign = 0;
  if( x < 0 )
      sign = 0x10000000 | newFloat;
  printf("\nsign: %08x\n", sign);
  
  //create exponent
  int exponent = 0;
  int leadingOneBit = 31;
  int mask = 0x40000000;
  //loop until the first 1 from the MSB is found
  while( !(mask & x) == 1 && leadingOneBit > 1) {
      leadingOneBit --;
      mask = mask >> 1;
  }
  exponent = leadingOneBit - 1;
  exponent = exponent + 127;
  //place exponent in designated 8 bits
  exponent = exponent << 23;
  printf("exponent: %08x\n", exponent);
  
  //create mantissa
  int mantissa = 0;
  int yo = 0x80000000 >> (32-leadingOneBit);
  int mantissaMask = ~((signed)0x80000000 >> (32-leadingOneBit));
  mantissa = mantissaMask & x;
  printf("yo: %08x\n", yo);
  printf("mantissa: %08x\n", mantissa);
  printf("mantissaMask: %08x\n", mantissaMask);
  printf("leadingOneBit: %d\n", leadingOneBit);
  
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
{ /*
  //testing if NaN (all 1's in exponent AND any 1's in the mantissa
  int expMask = (0xEF << 25);
  int mantissaMask = (0x1 << 23);
  if( ((uf & expMask) == expMask)  &&  ((mantissaMask & uf) != 0) )
      return uf;
    
  int newFloat;  
      
  //check for 0
  if( uf == 0 )
      return 0;    

  //retrieve the exponent and increment
  int exp = 0x7F800000 & uf;
  int newExp = exp + 0x00800000;
  int mask = 0x803FFFFF; 
  return newExp ^ uf;*/
  return 2;
}


