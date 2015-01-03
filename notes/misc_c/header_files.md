# Header files (wikipedia)

## Introduction

- causes the contents of a second file to be inserted in the original file (preprocessor)
- header files or copybooks
- often used to define physical layout of program data, forward declarations
- helps with encapsulation and reuse of code


## Purpose

- allows libraries of code to be developped
    - everyone uses the same version of data layout definition
    - easily cross-reference where components are used in a system
    - easily change programs when needed
    - save time by reusing data layouts

- useful when refering to functions in a different file (e.g. library)

~~~C
    int add(int, int);

    int triple(int x)
    {
      return add(x, add(x, x));
    }
~~~

Problem is, the function prototype must be present in all files
that use the add function, and if the return types are modified, they
must be modified everywhere.

Having the prototypes in a single separate file avoids these problems.

~~~C
    #include "add.h"

    int triple(int x)
    {
      return add(x, add(x, x));
    }
~~~

In C, header files should not include files (or use include guards).


## Include guards

- also called macro guards
- used to avoid *double inclusion* with the include directive
- makes the file idempotent (multiple includes will not break anything)


### Double inclusion problem

** File grandfather.h **

~~~C
    struct foo {
    int member;
    };
~~~

** File father.h**

~~~C
    #include "grandfather.h"

~~~

** File child.h**

~~~C
    #include "grandfather.h"
    #include "father.h"
~~~

- this will cause the C preprocessor to try to include twice grandfather.h file
- in C++ this is a violation of the One Definition Rule (in C, this causes fuckups)


the proper way to do it looks like that

** File grandfather.h **

~~~C
    #ifndef GRANDFATHER_H
    #define GRANDFATHER_H
    struct foo {
    int member;
    };
    #endif /* GRANDFATHER_H */
~~~

** File father.h**

~~~C
    #include "grandfather.h"

~~~

** File child.h**

~~~C
    #include "grandfather.h"
    #include "father.h"
~~~


### Syntax

- different naming conventions are used
- don't use double underscore __GRANDFATHER_H, this is reserved for compiler implementation and could cause serious problems
- crucial to avoid duplicating the name of a different include guard (hard to detect problem too)


### Difficulties

- most C implementations provide a non-standard #pragma once directive
    - ensures that the file is included only once
    - Objective-C uses #import directive, pretty much the same as #pragma once

