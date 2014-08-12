# Chapter 5: thinking of linking

## Libraries, Linking and Loading

### Basics
- compiler creates output file (.o), relocatable objects
- .o is the data and machine instructions corresponding to the source program

### When is the linker used?
- the compiler is most often split in many pieces
- makes it easier to maintain and more portable (modularity is generally good)
- optimization can happen at any step, usually in the intermediate representation (makes it portable)


### Overview of SPARCompiler
1. C preprocessor (copypasta machine)
2. front-end (syntax and semantic analysis)
3. back-end (code generation)
4. optimizer
5. assembler
6. link-loader


### Messing with the compiler

- can give options to a specified phase of compilation

~~~shell
	# -Wl specifies to give the instruction to the linker
	# -m means that the linker will create a linker map
	cc -Wl,-m main.c > main.linker.map
	# works on SVR4 architectures (not on current unix lol)
	# try this instead
	gcc -Wl,-Map,main.linker.map main.c
~~~


### What does it do really?

- an object file isn't directly executable
- linker identifies the main routine as the initial entry point
- linker binds symbolic references to memory addresses
- linker unites all the object files
- linker joins thme with the libraries to produce an executable


## Static and dynamic libraries

- static libraries: each library routine used goes into the executable
	- the library would be said to be statically linked
	- obviously, the executable is bigger than those dynamically linked
- dynamic libraries: program looks at runtime for the routines
- 3 steps in collecting modules together and preparing them for execution
	- link-edition
	- loading
	- runtime linking


### Benefits of dynamic linking

- smaller executable size
- more efficient use of the disk (not that relevant now in most cases)
- quicker link-edit phase for a small runtime penalty
- allows interface development (*Application Binary Interface*, ABI)
- ABI allows a level of abstraction
- allows easy versioning of libraries (in theory, but some version specific)
- in theory, allows user to select runtime characteristics
	- create library versions for different tradeoffs (speed, mem, debug, ...)
- dynamic linking is **just-in-time** linking


### Downsides of dynamic linking

- must be able to find lib location at runtime
- architecture specific (must have the good version for environment)
- still better than static linking, where the executable will not be portable at all


## Compilation options for dynamic libraries

- **fPIC**: produce position-independent code for libs
	- global data access is done through extra indirection
	- easier to relocate the data by changing a value in the table of global offsets

- **shared**: Produce a shared object which can then be linked with other objects


### Five special secrets of linking with libraries

1. dynamic libraries are **.so**, shared libraries are **.a**
2. can link by givin explicit option e.g. libthread **-libthread**
3. compiler expects to find the libraries in certain directories
	- /usr/lib/
	- /usr/lib/libthread.so
4. identify your libraries by looking at the header files you have used
	- in the man page (man sin will tell you it is in math.h, -lm)
	- inconsistent behavior however, need to know some of them
5. symbols from static libraries are extracted in a more restricted way than symbols from dynamic libraries
6. **always put the -l library options at the rightmost end of the compile call**
	- most common is lib math, which is statically linked for more performance
	- statically linked symbols are extracted only if necessary
	- if you mention the static libraries before your own code there won't be any undefined symbols yet, so nothing will be extracted.


### Interpositioning

- supplanting a library function by a user-written function of the same name
- useful for debugging or performance
- easy to fuck up (nasty, hard to find bugs, but it is supposed to work this way)
- all calls from *system routines* now call your function
- **index** and **mktemp** cause bugs often
- don't make any symbols in your program global, unless you want to use them for interface
- **check the reserved words for the C implementation**

