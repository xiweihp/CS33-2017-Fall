/* 
 * CS:APP Data Lab 
 * 
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

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
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

EXAMPLES OF ACCEPTABLE CODING STYLE:
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

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
/*
 *  return 1 only when x is zero.
 *  So shift all possible 1 to the LSB.
 *  Then determine is there any 1 in the bits.
 */
  x = x|(x>>1);
  x = x|(x>>2);
  x = x|(x>>4);
  x = x|(x>>8);
  x = x|(x>>16);
  return (~x&1);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
/* use shift to build a mask in pattern 0001 ... 0001 to divide it to bits of four.
 * Then shift x to get every possible 1s and add to groups of every four bits.
 * Calculate the sum of each group and add together.
 */
  int mask = 0x11;
  mask += (mask << 8);
  mask +=  (mask << 16); 
  x = (x & mask) + (x >> 1 & mask) + (x >> 2 & mask) + (x >> 3 & mask);
  return  (x & 0xf) + (x >> 4 & 0xf) + (x >> 8 & 0xf) + (x >> 12 & 0xf) + (x >> 16 & 0xf) + (x >> 20 & 0xf) + (x >> 24 & 0xf) + (x >> 28 & 0xf);
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
/* the same logic as DeMorgan's Law 
 */
  int a = ~x;
  int b = ~y;
  int c = a&b;
  return ~c;
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
/* Set a parameter to make sure the shifted amount is defined. 
 * repeatedly process for 5 shifts.
 */
  int max = (n - 32) >> 31;
  int repeat = x & (~(-1 << n));
  repeat += repeat << n;
  repeat += (repeat << n * 2) & ((n - 16) >> 31);
  repeat += (repeat << n * 4) & ((n - 8) >> 31);
  repeat += (repeat << n * 8) & ((n - 4) >> 31);
  repeat += (repeat << n * 16) & ((n - 2) >> 31); 
  return ((~max) & x)|(max & repeat);
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
int fitsBits(int x, int n) {
/*right shift x by (n-1) (-1 is for the sign bit);
 *Depends on its original sign, determine whether the shorter bits is eligible
 */
  int shift = x >> (n + ~0); 
  return (!shift)|(!(~shift));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
/*n left shift 3 to get n*2^3, the number of bits need to mask off. 
 *Then right shift back,
 *keep only the first byte from LSB
 */
  int shift = n << 3;
  int mask = x&(~0<<shift);
  int shiftBack = mask >> shift;
  return shiftBack&0xFF;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
/*
 *When x == INT_MIN, always return 1.
 *When x and y are in same sign and x != INT_MIN:
 *then only when y+(-x)>=0, return 1.
 *When x and y are in different sign:
 *then only when x is negative, return 1.
 */
  int isMIN = !(x^(1<<31));
  int xySame = !(((x>>31)&1)^((y>>31)&1));
  int xNegative = ((x>>31)&1);
  int ans = y + ( ~x + 1 );
  int ansNegative = ((ans >> 31)&1);

  return isMIN|((!ansNegative)&(xySame))|((!xySame)& (xNegative));


}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
/*
 *right shifting by 31 and masking using 1, 
 *can determine the nonnegativeness of the value.
 *Then exclude the situation when x is zero.
 */
  int nonNegative = !((x>>31)&1);
  int isZero = !x;
  return nonNegative & (!isZero);

}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
/*
 *left shift 1 by 31 and then right shift by (n-1) can form the mask.
 */
  int mask = ~(((1<<31)>>n)<<1);
  int ashift = x>>n;
  return (ashift & mask);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
/*create a number with all bits equal 1, 
 *then left shift it to get all bits except MSB equal 0. 
 */

  return (1<<31);
}
