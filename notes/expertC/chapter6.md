# Chapter 6: Poetry in motion: runtime data structures

## a.out and a.out folklore

- stands for *assembler output*
- it actually is the linker output
- purely historical (on the PDP-7 there was no linker)


## Segments

- object files and executables come into one of several different formats
- **ELF**: Extensible Linker Format orignally, now Executable Linking Format
- in object files: areas within a binary file where a type of (e.g., symbol table entries) is kept
- **not the same as segments in x86 memory model !**


### Checking out the segments in an executable

~~~shell
    # we can use the unix command size to see what is the size of
    # the sections of an executable or archive file (text, data, bss)
    size a.out
    
    # we can list the symbols of an object file using the nm command
	# this allows us to explore the different segments of the file
	# (text, data, bss)
    nm a.out
~~~


## What goes into the segments

- 3 segments
	- text: executable instructions
	- data: initialied global and static variables
	- bss: unitialized data
		- **b**lock **s**tarted by **s**ymbol, a pseudo-op from IBM 704 assembler
		- *also know by Better Save Space*, the size BSS requires at runtime is recorded in the object file

~~~C
	/* first program */
	#include <stdio.h>

	int main()
	{
		printf("Hello world\n");
		return 0;
	}

	/* its size is the following */
	/*
    text	   data	    bss	    dec	    hex	filename
    1214	    560	      8	   1782	    6f6	a.out
	*/

   /* second program */
	#include <stdio.h>

	int main()
	{
		int a[1000];
		a[0] = 0;
		printf("Hello world\n");
		return 0;
	}

	/* its size is the following */
	/*
    text	   data	    bss	    dec	    hex	filename
    1230	    560	      8	   1798	    706	a.out
	*/
~~~

- data segment is kept in the object file
- BSS isn't kept in the object file (except for a note of runtime size requirements)
- text segment is the more sensitive to optimization
- a.out file is affected by compiling for debugging, but the segments are not


## What does the OS do with a.out

- the segments map into objects the runtime linker can load directly
- loader just takes each segments image and put it in memory
- **the segments become memory areas of an executing program, each with dedicated purpose**



## What the C runtime does with a.out


### Stack segment

- single data structure (stack), LIFO
- real-world, possible to change values in the stack
- function can access local variable via global pointer
- runtime maintains pointer (register) **sp**, the stack pointer, current top of the stack
- **3 main uses**
	- storage area for local variables declared inside functions (automatic variables)
	- stores stack frame aka activation record, information involved in a function call
	- push partial results of evaluations and pop them when necessary (through alloca())
- essential for recursion
- stack grows downward (in addresses)

~~~C
	/* can figure out the address of the top of the stack this way */
	#include <stdio.h>
	main()
	{
		int i;
		printf("The stack top is near %p\n", &i);
		return 0;
	}
~~~


### Procedure activation record (what happens when a function gets called)

- runtime must keep call chain
	- which routines have called which others
	- where the control will pass back to (ret statement)
- managed by the activation record

~~~
	meta structure
	- local variables
	- arguments
	- static link (for uplevels references; not used in C)
	- ptr to previous frame
	- return address (function pointer fp)
~~~

- C doesn't allow function nesting (in definitions)
	- them being all at top lexical level simplifies implementation
	- no static uplink

~~~C
	/* example of  */
	void a(int i)
	{
		if (i>0)
		{
			a(--i);
		}
		else
		{
			printf("i has reached zero");
		}
		return;
	}

	main()
	{
		a(1);
	}
~~~

- compiler writes speed up programs by not storing useless information
- a stack frame might be allocated in registers for performance


### auto and static keywords

~~~C
	char * f()
	{
		char a [] = "apple";  /* a is allocated on the stack */
		return a;  /* return a pointer to a on the stack */
	}
	/* after the end of f(), the stack frame is cleaned */
~~~

if you really want to return a pointer, not on the stack, use the *static* keyword



### setjmp and longjmp

- implemented by manipulating activation records
- compensate for C's limited branching capabilities

~~~C
	setjmp(jmp_buf j)
	/* j will remember the position (program counter and stack address) */

	longjmp(jmp_buf j, int i)
	/* will go back to the place j is remembering
	   returns i, so the code can tell it actually got back */
~~~






