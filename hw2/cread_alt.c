/*3.61*/
long cread_alt(long *xp)
/*
 *dereference a null pointer cause problem in original code.
 *so first assign only the correct adress to register to make sure 
 *the adress of returning value is not null 
 *and then dereference it.
 */
{
	long a = 0;
	return *(xp ? xp : &a);
}


