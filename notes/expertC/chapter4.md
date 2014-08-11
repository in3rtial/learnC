# Chapter 4: C arrays and pointers

## Arrays are not pointers

~~~C
    /* different declarations */
    extern int *x; /* a pointer to int */
    extern int y[]; /* array of int of unspecified size */

    /* file 1 */
    int mango[100];

    /* file 2 */
    extern int * mango; /* this is wrong! */

    
~~~


