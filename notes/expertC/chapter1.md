# Chapter 1 C through the mist of time

## Early experiences with C
- arrays start from 0 instead of 1
- fundamental C types map directly onto underlying hardware
- array names in expressions decay into pointers
- floating-point expressions were expanded to double-length-precision

- no nested functions
- register keyword: just don't use it

## Which version of C to use?
Should be using ANSI C, not K&R C. Should remember that the book
was written in 1994, way before c99...

## Translation limits
ANSI C compiler are required to support at least
- 31 parameters in function definition
- 31 arguments in a function call
- 509 characters in a source line
- 32 levels of nested parentheses in an expression
- long int are at least 32 bits

## Const
Doesn't turn a variable into a constant. It just means that the 
variable is read-only through that symbol. Could be modified by
internal or external mechanism.

## Unsigned types
- Don't use them, even for types where the quantity will never be negative (age...).
- Only use for bitfields or binary masks.

## GCC pragmas
- borrowed from Ada
- used to convey hints to the compilers
- implementation defined (gcc...), use only if necessary

