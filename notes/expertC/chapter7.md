# Chapter 7: thanks for the memory


### How much memory can be allocated

just run this

~~~C
    /* this will likely freeze your computer... */ 
    #include <stdio.h>
    #include <stdlib.h>
    main() {
      int Mb = 0;
      while ( malloc(1<<20)) ++Mb;
      printf("Allocated %d Mb total\n", Mb);
    }
~~~


### Catching signals

to write a signal handler (e.g. to get ctrl-c), use the **<signal.h>**


### Segmentation fault

- violation in memory management
- usually caused by dereferencing a pointer with an uninitialized or illegal value


### Freeing elements in a linked list

~~~C
  /* how to free a linked list */
  struct node *p, *start, *tmp;
  for (p=start; p; p=tmp)
  {
    tmp=p->next;
    free(p);
  }
~~~

### Signal handler to catch a system signal

~~~C
  #include <signal.h>
  #include <stdio.h>
  void handler(int s)
  {
    if (s == SIGBUS) printf(" now got a bus error signal\n");
    if (s == SIGSEGV) printf(" now got a segmentation violation signal\n");
    if (s == SIGILL) printf(" now got an illegal instruction signal\n");
    exit(1);
  }

  main ()
  {
    int *p=NULL;
    signal(SIGBUS, handler);
    signal(SIGSEGV, handler);
    signal(SIGILL, handler);
    *p=0;
  }
~~~
