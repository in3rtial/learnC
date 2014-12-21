/* just messing around to see if there is any improvements by signaling a function
   as being pure to gcc
   https://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
*/


#include "t1.h"
#include <stdio.h>


int main ()
{
	int a = 13;
	double b = square(a);
	printf("%f\n", b);
  return 0;
}
