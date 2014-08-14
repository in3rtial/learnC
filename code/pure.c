/* just messing around to see if there is any improvements on by signaling a function
   as being pure */

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
