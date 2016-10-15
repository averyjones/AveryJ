/* Testing Code */

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "bits.h"

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
  union {
    unsigned u;
    float f;
  } a;
  a.f = f;
  return a.u;
}

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

int test_bitAnd(int x, int y)
{
  return x&y;
}


int test_getByte(int x, int n)
{
    unsigned char byte;
    switch(n) {
    case 0:
      byte = x;
      break;
    case 1:
      byte = x >> 8;
      break;
    case 2:
      byte = x >> 16;
      break;
    default:
      byte = x >> 24;
      break;
    }
    return (int) (unsigned) byte;
}


int test_logicalShift(int x, int n) {
  unsigned u = (unsigned) x;
  unsigned shifted = u >> n;
  return (int) shifted;
}


int test_bitCount(int x) {
  int result = 0;
  int i;
  for (i = 0; i < 32; i++)
    result += (x >> i) & 0x1;
  return result;
}


int test_bang(int x)
{
  return !x;
}


int test_tmin(void) {
  return 0x80000000;
}


int test_fitsBits(int x, int n)
{
  int TMin_n = -(1 << (n-1));
  int TMax_n = (1 << (n-1)) - 1;
  return x >= TMin_n && x <= TMax_n;
}


int test_divpwr2(int x, int n)
{
    int p2n = 1<<n;
    return x/p2n;
}


int test_negate(int x) {
  return -x;
}


int test_isPositive(int x) {
  return x > 0;
}


int test_isLessOrEqual(int x, int y)
{
  return x <= y;
}


int test_ilog2(int x) {
  int mask, result;
  /* find the leftmost bit */
  result = 31;
  mask = 1 << result;
  while (!(x & mask)) {
    result--;
    mask = 1 << result;
  }
  return result;
}


unsigned test_float_neg(unsigned uf) {
    float f = u2f(uf);
    float nf = -f;
    if (isnan(f))
 return uf;
    else
 return f2u(nf);
}


unsigned test_float_i2f(int x) {
  float f = (float) x;
  return f2u(f);
}


unsigned test_float_twice(unsigned uf) {
  float f = u2f(uf);
  float tf = 2*f;
  if (isnan(f))
    return uf;
  else
    return f2u(tf);
}


int main(int argc, char *argv[]){

//Test Cases for bitAnd 
assert(bitAnd(7,8)==test_bitAnd(7,8)); 
assert(bitAnd(1,3)==test_bitAnd(1,3));
assert(bitAnd(9,8)==test_bitAnd(9,8));
assert(bitAnd(0,6)==test_bitAnd(0,6));
assert(bitAnd(255,254)==test_bitAnd(255,254));
printf("Passed Test Cases for bitAnd\n");

//Test Cases for getByte 
assert(getByte(0x12345678,1)==test_getByte(0x12345678,1)); 
assert(getByte(0,0)==test_getByte(0,0));
assert(getByte(0x12345678,2)==test_getByte(0x12345678,2));
assert(getByte(0x12345678,3)==test_getByte(0x12345678,3));  
printf("Passed Test Cases for getByte\n");

//Test Cases for logicalShift
assert(logicalShift(0x87654321,4)==test_logicalShift(0x87654321,4));
assert(logicalShift(0x87654321,0)==test_logicalShift(0x87654321,0));
assert(logicalShift(0x87654321,31)==test_logicalShift(0x87654321,31));
printf("Passed Test Cases for logicalShift\n");

//Test Cases for bitCount
//printf("Passed Test Cases for bitCount\n");

//Test Cases for bang
assert(bang(3)==test_bang(3));
assert(bang(0)==test_bang(0));
assert(bang(-5)==test_bang(-5));
assert(bang(0xFFFFFFFF)==test_bang(0xFFFFFFFF));
assert(bang(0x80000000)==test_bang(0x80000000));
printf("Passed Test Cases for bang\n");

//Test Cases for tmin
assert(tmin()==test_tmin());
printf("Passed Test Cases for tmin\n");

//Test Cases for fitsBits
assert(fitsBits(5,3)==test_fitsBits(5,3));
assert(fitsBits(-4,3)==test_fitsBits(-4,3));
printf("Passed Test Cases for fitsBits\n");

//Test Cases for divpwr2
//printf("Passed Test Cases for divpwr2\n");

//Test Cases for negate
assert(negate(1)==test_negate(1));
assert(negate(4)==test_negate(4));
assert(negate(-4)==test_negate(-4));
assert(negate(1)==test_negate(1));
assert(negate(0)==test_negate(0));
printf("Passed Test Cases for negate\n");

//Test Cases for isPositive
assert(isPositive(2)==test_isPositive(2));
assert(isPositive(-10)==test_isPositive(-10));
assert(isPositive(0)==test_isPositive(0));
assert(isPositive(0xF0000000)==test_isPositive(0xF0000000));
assert(isPositive(0xEFFFFFFF)==test_isPositive(0xEFFFFFFF));
printf("Passed Test Cases for isPositive\n");

//Test Cases for isLessOrEqual
//printf("Passed Test Cases for isLessOrEqual\n");

//Test Cases for ilog2
//printf("Passed Test Cases for ilog2\n");

//Test Cases for float_neg
assert(float_neg((unsigned)1)==test_float_neg((unsigned)1));
assert(float_neg((unsigned)0)==test_float_neg((unsigned)0));
assert(float_neg((unsigned)20)==test_float_neg((unsigned)20));
assert(float_neg((unsigned)-20)==test_float_neg((unsigned)-20));
assert(float_neg((unsigned)255)==test_float_neg((unsigned)255));
assert(float_neg((unsigned)-255)==test_float_neg((unsigned)-255));
printf("Passed Test Cases for float_neg\n");

//Test Cases for float_i2f
assert(float_i2f(1)==test_float_i2f(1));
assert(float_i2f(0)==test_float_i2f(0));
assert(float_i2f(-20)==test_float_i2f(-20));
assert(float_i2f(255)==test_float_i2f(255));
assert(float_i2f(-255)==test_float_i2f(-255));
printf("Passed Test Cases for float_i2f\n");

//Test Cases for float_twice
printf("\nfloat_twice(-255.56): %0x8\n", float_twice(0xc37f8f5c));
printf("test_float_twice(-255.56): %0x8\n", test_float_twice(0xc37f8f5c));
/*1*/assert(float_twice(0x3f800000)==test_float_twice(0x3f800000));
/*0*/assert(float_twice(0)==test_float_twice(0));
/*-1*/assert(float_twice(0xbf800000)==test_float_twice(0xbf800000));
/*20*/assert(float_twice(0x41a00000)==test_float_twice(0x41a00000));
/*-20*/assert(float_twice(0xc1a00000)==test_float_twice(0xc1a00000));
/*10.2*/assert(float_twice(0x41233333)==test_float_twice(0x41233333));
/*-10.2*/assert(float_twice(0xc1233333)==test_float_twice(0xc1233333));
/*-10.56*/assert(float_twice(0x4128f5c3)==test_float_twice(0x4128f5c3));
printf("Passed Test Cases for float_twice\n");


return 0;

}
