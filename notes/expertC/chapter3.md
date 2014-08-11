# Chapter 3: Unscrambling declarations in C


## Hard to read declarations

~~~C
    /* pointer declaration */
    char (*j)[20]; /* j is pointer to an array of 20 char */
    j = (char (*) [20]) malloc(20); /* must keep (*) otherwise invalid */

    /* const */
    const int * grape; /* int read-only */
    int const * grape; /* int read-only */
    int * const grape_jelly; /* pointer read-only */

~~~


### Function return types

- function can't return a function: no foo()()
- function can't return an array: no foo() []
- array can't hold a function: no foo[]()

- function returning a pointer to a function is allowed: int (* fun ())()
- function returning a pointer to an aray is allowed: int (* foo())[]
- array holding pointers to functions is allowed: int (*foo[])()
- array can hold other arrays: int foo[][]


### Structs

~~~C
    /* structs are just a bunch of data items grouped together */
    struct optional_tag {
          type_1 identifier_1;
          type_2 identifier_2;
          ...
          type_N identifier_N;
    } optional_variable_1, optional_variable_n;

    /* it is possible to declare padding explicitely */
    struct pid_tag {
      unsigned int inactive :1; /* 1 bit of padding */
      unsigned int          :1;
      unsigned int refcount :6;
      unsigned int          :0;
      short pid_id;
      struct pid_tag *link;
    };
    
    
~~~

p.66