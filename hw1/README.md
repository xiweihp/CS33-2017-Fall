Homework1:
-----
Do homework problems 2.62, 2.72, 2.73, and 2.82
------
Check your 2.62 solution with both gcc -m32 and gcc -m64 on SEASnet;
------
In problem 2.82, also analyze the following expressions:
F.
x >> 1 == (ux >> 1) + (ux & (-1 << 31))
G.
x % 128 == (x & 127)
------
Redo problem 2.73, this time using a call to the __builtin_add_overflow_p function available in GCC 7 and later; 
the third argument of the call should be a cast that consists of a parenthesized type followed by the constant 0. 
In other respects your function should continue to follow the bit-level integer coding rules.
