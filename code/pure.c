/* just messing around to see if there is any improvements by signaling a function
   as being pure to gcc
   https://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
*/

int square (int) __attribute__ ((pure));


int square (int x)
{
	return x * x;
}



int main ()
{
	int a = 13;
	int b = square(a);
	return 0;
}
