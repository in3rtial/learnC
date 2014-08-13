# Chapter 2: It's not a bug, it's a language feature

## language features, the fortran bug (NASA)

- on an orbital trajectories calculator

~~~fortran
    !blank characers are not significant and can occur in the middle of an identifier
    !this declares DO10I = 1.10
    DO 10 I=1.10

    !instead of a looping construct (. instead of ,)
    DO 10 I=1,10

    !was corrected in time and never caused a Mercury space flight to fail
~~~

in C, a common example is to forget the null character in malloc declaration e.g.
malloc(strlen(str)) instead of malloc(strlen(str)+1)

## different types of sins
- sins of comission: things the language does but shouldn't do
- sins of omission : things the language doesn't do that it should
- sins of mission : things that are completely off the wall...

## NUL and NULL
- The one 'l' NUL ends an ASCII string.
- The two 'l' NULL points to no thing.
- The three 'l' NULLL means check your spelling... lol



## Sins of commission

### Switches let you down with fall through

~~~C
    switch (expression) {
      case constant-expression: zero-or-more-statements
      default: zero-or-more-statements
      /* FALLTHRU */
      case constant-expression: zero-or-more-statements
    }
~~~

- constant-expression forbids const types, since they aren't really constant
- fall through is in most case unwanted (break is rarely missing for a reason)

### AT&T's break bug
- can only break out of a loop statement
- programmer wanted to break out of an "if" statement


### different action first time through
~~~C
    {
      static char separator='';
      printf("%c %s \n", separator, string);
      separator = ',';
    }
~~~


### too much default visibility
- function name are globally visible by default
- same as extern basically
- static keyword will restrict the visibility (also allows compiler optimization I think)
- user-written functions replace library defined functions
- all-or-nothing visibility, symbols are either globally known or no at all

~~~c
  function apple (){ /* visible everywhere */ }
  extern function pear () { /* visible everywhere */ }
  static function turnip(){ /* not visible outside this file */ }
~~~



## Sins of mission

### Symbol overloading


| symbol      |   meaning                                              |
| ----------- |:------------------------------------------------------:|
| static      |   inside function = retains its value between calls    |
|             |   function = visible only in this file                 |
| extern      |   function = global scope (default)                    |
|             |   variable = defined elsewhere                         |
| void        |   type = no value returned                             |
|             |   pointer = generic pointer                            |
|             |   parameter = takes no parameter                       |
| \*          |   number = multiplication                              |
|             |   pointer = indirection                                |
|             |   declaration = pointer                                |
| &           |   bitwise AND                                          |
|             |   address-of operator                                  |
| = and ==    |   assignment operator                                  |
|             |   comparison operator                                  |
| <= and <<=  |   less-than-or-equal                                   |
|             |   compound shift-left assignment operator              |
| < and <     |   less-than operator                                   |
|             |   left delimiter in include directive                  |
| ()          |   parameters                                           |
|             |   function call                                        |
|             |   precedence cast                                      |
|             |   macro declaration and usage                          |


### Operator precedence
- simply the order in which the functions are evaluated
- use parentheses, operator precedence is recognized as being crappy


### Operator associativity
- tie-breaker for operators with equal precedence


### Order of evaluation
- mostly unspecified (&& and || are specified left to right)
    - allows compiler writers some leeway
    - order of evaluation of function argument isn't even left to right!!!
    
~~~C
    #include <stdio.h>

    int main()
    {
       int a[] = {1, 2, 3};
       int * pa; 

       pa = &a[0];
       printf("a[0] = %d\ta[1] = %d\ta[2] = %d\n",*(pa), *(pa++),*(++pa));
       /* Result: a[0] = 3  a[1] = 2    a[2] = 2 */

       pa = &a[0];
       printf("a[0] = %d\ta[1] = %d\ta[2] = %d\n",*(pa++),*(pa),*(++pa));
       /* Result: a[0] = 2  a[1] = 2     a[2] = 2 */

       pa = &a[0];
       printf("a[0] = %d\ta[1] = %d\ta[2] = %d\n",*(pa++),*(++pa), *(pa));
       /* a[0] = 2  a[1] = 2 a[2] = 1 */

      /* BE VERY CAREFUL ! */
    }

~~~


### gets() bug and the internet worm
- propagated through a weakness in the finger daemon, which accepts queries over the network about who is currently logged in.
- gets() reads a string from a stream but doesn't check buffer space
- will overwrite the stack

~~~C
    main(argc, argv)
    char *argv[];
    {
    char line[512];
    /* gets will overwrite after the line pointer if fed more than 512 bytes of data */
    gets(line);
    /* if you put a well crafted return address to call execv() to start a shell... */
    }
~~~

- this was "fixed" by using fgets which specifies the array size to copy into



## Sins of omission


### Argument parsing
- mail failed if user had 'f' characters in position 2 of their name
- was caused by shitty input convention from command line

~~~C
    if ( argv[argc-1][0] == '-' || (argv[argc-2][1] == 'f' ) )
      readmail(argc, argv);
    else
      sendmail(argc, argv);
~~~

which is problematic because of the ways the program can be called

~~~bash
    # normally
    mail -h -d -f /usr/linden/mymailbox

    # but this call is also possible
    mail effie robert
~~~


### Space problems
- whitespace isn't insignificant
- newline escape vs \ whitespace newline

~~~C
    /* z = y + ++x but instead z = y++ + x */
    z = y+++x;

    /* z = y++ ++ + x */
    z = y+++++x;

    /* comment system fuckup */
    ratio = *x/*y;

~~~


### Comment system
- omitting to close a comment can go undetected and a piece of code disappears


### String creation
- can return reference to a buffer that is locally allocated buffer (automatic allocation)
- these buffer can be overwritten immediately or later, making it difficult to debug
- use malloc to allocate (in the style of fgets with a size limit and verification)


### Lint should have been kept with the compiler
- use Splint (free open source version of old-school lint)
- also interesting version that verify compliance with MISRA C and other fancy stuff
