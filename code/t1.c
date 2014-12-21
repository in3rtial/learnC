/* just messing around to see if there is any improvements by signaling a function
   as being pure to gcc
   https://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
*/


double square (int x)
{
	return x * x;
}

/*
double square(double x)
{
  return x * x;
}
*/

