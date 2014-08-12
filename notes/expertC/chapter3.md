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

~~~C
    /* NOT ALLOWED */
    /* function can't return a function */
    foo()()

    /* function can't return an array */
    foo() []

    /* array can't hold a function */
    foo[]()

    /* ALLOWED */
    /* function returning a pointer to a function is allowed */
    int (* fun ())()

    /* function returning a pointer to an aray is allowed */
    int (* foo())[]

    /* array holding pointers to functions is allowed */
    int (*foo[])()

    /* array can hold other arrays */
    int foo[][]
~~~

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


### Unions

~~~C
    /* - pretty rarely used
       - C says go fish, and relies on the programmer to remember what was put there */
    union optional_tag {
      type_1 identifier_1;
      type_2 identifier_2;
      ...
      type_N identifier_N;
      } optional_variable_definitions;
~~~


### enums

~~~C
    /* declaration format */
    enum optional_tag {stuff... } optional_variable_definitions;

    /* example */
    enum sizes { small=7, medium, large=10, humungous };
~~~


### Declaration parsing
- declarations are read boustrophedonically (alternating -> and <-)

~~~C
    void (*signal(int sig, void (*func)(int)) ) (int);
    void (*signal(                          ) ) (int);
~~~

### Typedef
- new name for a type
- can omit struct keyword
- don't bother with typedefs for structs (should be explicit about it anyways)


### Further readings
- check out Data Structures with Abstract Data Types













