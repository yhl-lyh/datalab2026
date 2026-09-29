/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if((!x) ^ (!y))
    {
        return 0;
    }
    else
    {
        if((x >> 31) ^ ((y >> 31)))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int a, b, c, d, e;
    
    a = ((v >> 16) > 0) << 4;
    v = v >> a;

    b = ((v >> 8) > 0) << 3;
    v = v >> b;

    c = ((v >> 4) > 0) << 2;
    v = v >> c;

    d = ((v >> 2) > 0) << 1;
    v = v >> d;

    e = ((v >> 1) > 0);

    return a | b | c | d | e;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {

    int sn = n << 3;
    int sm = m << 3;

    int ln = ((x >> sn) & 0xFF) << sm;
    int lm = ((x >> sm) & 0xFF) << sn;

    int cleared = x & ~((0xFF << sn) | (0xFF << sm));

    return cleared | ln | lm;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned result = 0;
    int i = 32;
    while(i)
    {
        result = (result << 1) | (v & 1);
        v = v >> 1;
        i--;
    }
    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    return (x >> n) & ~(((1 << 31) >> n) << 1);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {

    x = ~ x;
    int y = !x;

    int a, b, c, d, e;

    a = (!(x >> 16)) << 4;
    x = x << a;

    b = (!(x >> 24)) << 3;
    x = x << b;

    c = (!(x >> 28)) << 2;
    x = x << c;

    d = (!(x >> 30)) << 1;
    x = x << d;

    e = !(x >> 31);

    return a + b + c + d + e + y;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if (x == 0)
        return 0;

    unsigned sign = x & 0x80000000;
    unsigned ux = x;

    if (sign) {
        ux = -ux;
    }

    int i = 31;

    while (i + 1) {
        if (ux >> i) {	
            break;
        }
        else {
            i = i - 1;
        }
    }

    if (i > 23) {
        int shift = i - 23;
        unsigned kept = ux >> shift;
        unsigned remainder = ux & ((1 << shift) - 1);
        unsigned half = 1 << (shift - 1);
        int round_up = 0;

        if (remainder > half) {
            round_up = 1;
        }
        else if ((remainder == half) & (kept & 1)) {
            round_up = 1;
        }

        ux = kept + round_up;

        if (ux >> 24) {
            ux = ux >> 1;
            i = i + 1;
        }
    }
    else {
        ux = ux << (23 - i);
    }

    ux = ux & 0x007FFFFF;

    unsigned result = sign | ((i + 127) << 23) | ux;

    return result;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = uf & 0x7F800000;
    unsigned frac = uf &0x007FFFFF;
    if(exp == 0x7F800000)
    {
        return uf;
    }
    else if(exp == 0x00000000)
    {
        return sign | (frac << 1);
    }
    else if(exp == 0x7F000000)
    {
        return sign | 0x7F800000;
    }
    else
    {
        return sign | (exp + 0x00800000) | frac;
    }
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 & 0x80000000;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    int e = exp - 1023;
    unsigned uf2_frac = uf2 & 0xFFFFF;
    if(e < 0)
    {
        return 0;
    }
    else if(e > 30)
    {
        return 0x80000000;
    }

    unsigned result;

    if(e < 20)
    {
        result = (1 << e) | (uf2_frac >> (20 - e));
    }
    else
    {
        result = (1 << e) |(uf2_frac << (e - 20)) | (uf1 >> (52 - e));
    }

    if(sign)
    {
        return -result;
    }
    else
    {
        return result;
    }
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127) {
        return 0x7F800000;
    }
    else if (x >= -126) {
        return (x + 127) << 23;
    }
    else if (x >= -149) {
        return 1 << (x + 149);
    }
    else {
        return 0;
    }
}
