# Chapter 4: C arrays and pointers

## Arrays are not pointers


### Problematic case
~~~C
    /* different declarations */
    extern int *x; /* a pointer to int */
    extern int y[]; /* array of int of unspecified size */

    /* file 1 */
    int mango[100];

    /* file 2 */
    extern int * mango; /* this is wrong! */

~~~


### Declaration and definition
- arrays and pointers are equivalent under certain circumstances
- definition: unique, specifies the type of an object and its storage
- declaration: can happen multiple times, describes the type of the object, compiler information (e.g. prototypes)


### How arrays and pointers are accessed
- difference between an address (l-value) and its content (r-value)

~~~C
    /* this is an example:
      x is the address of y, the left value, the locator
      y is the value at address x, the right value */
    x = y;
~~~

- the compiler allocates and address to each variable -> it knows their values at compile time
- the r-values, however, is only decided at runtime in most cases
- if the value of a variable is required, must read the value from the given address and put it in a register

~~~C
    /* subscripted array reference */
    char a[9] = "abcdefgh";
    char c = a[i];
    /* to do that:
        1 - get value i and add it to value a
        2 - get the contents from address (a + i)
    */

    /* pointer reference */
    char *p;
    c = *p;
    /* to do that:
        1 - get the contents of the address at p
        2 - use the content and return what is at the address
    */

    /* subscripted pointer reference */
    char *a = "abcdefgh";
    char c = a[i];
    /* to do that:
        1 - get the content at address a
        2 - get the value i and add it to value a
        3 - get the content from the address (a + i)
    */

    /* basically, there's one more dereference step
       when using a subscripted pointer reference instead of a subscripted array reference
    */
~~~

and that is enough to fuck up



### Match your declarations to the definition

~~~C
    /* file 1 */
    int mango[100];

    /* file 2 */
    extern int mango[];
    ...
~~~


### Other differences between arrays and pointers
p.92



