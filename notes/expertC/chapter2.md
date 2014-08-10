# Chapter 2: It's not a bug, it's a language feature

## language features, the fortran bug (NASA)

- on an orbital trajectories calculator
- DO 10 I=1.10 instead of DO 10 I=1,10 (. instead of ,)
- blank characers are not significant and can occur in the middle of an identifier
- DO10I = 1.10 instead of DO 10 I = 1, 10
- was corrected in time and never caused a Mercury space flight to fail

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
~~~
switch (expression) {
	case constant-expression: zero-or-more-statements
	default: zero-or-more-statements
	/* FALLTHRU */
	case constant-expression: zero-or-more-statements
	}
~~~

- constant-expression forbids const types, since they aren't really constant
- fall through means that 


### AT&T's break bug
- can only break out of a loop statement
- programmer wanted to break out of an "if" statement


### first time through
- getting a differnet action the first time through the function
~~~c
generate_initializer(char * string)
{
	static char separator='';
	printf("%c %s \n", separator, string);
	separator = ',';
}
~~~

### too much default visibility
- function name are globally visible by default
- can use exern
