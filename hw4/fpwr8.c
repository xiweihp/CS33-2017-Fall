
/*except compute 8**x rather than 2**x and 
 *call the resulting function fpwr8 instead 
 *of fpwr2. Submit a source-code file named 
 *'fpwr8.c' that contains all the source code 
 *for fpwr8, preceded by the definition of a 
 *function 'static float u2f(unsigned u) { ... }' 
 *that returns a value as described in 2.90 
 *(you fill in the "...").
 */

static float u2f(unsigned u) 
{
	union castu
	{
		unsigned a;
		float b;
	};
	castu.a = u;
	return cast.b;
}

float fpwr8(int x)
/*compute a floating point representation of 8**x */
{
	/*result exponent and fraction */
	unsigned exp, frac;
	unsigned u;

	if( x < -49 )/* 8**x = 2**(3x) */
	{   /*smallest denormalized: 2^(-23-126)*/
		/*too small , return 0.0*/
		exp = 0;
		frac = 0;
	}
	else if (x < -42)/* 3x < -126*/
	{
		/* Denormalized result*/
		exp = 0;
		frac = 1 << (149 + 3*x);/* 2^(3x)* 2^(23 + 126) */
	}
	else if (x < 43)/* 3x < 128*/
	{
		/*Normalized*/
		exp =  3*x + 127;/* 2^(3x + 127)*/
		frac = 0 ;
	}
	else
	{
		/*too big return +oo*/
		exp = 255;
		frac = 0;
	}
	/* Pack exp and frac into 32 bits*/
	u = exp << 23 | frac;
	/*return as float*/
	return u2f(u);

}
