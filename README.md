# Better C stdio

This library adds simple implimentations that improve the "quality of life" in programming. By adding features such as immutable/dynamic strings, you no longer have to sacrifice qualities found in other slower programming languages. By adding this library, you will have access to the following:
- Immutable/Dynamic Strings
- Easy Linked Lists

  
## Motivation for Creation

Over time, more will be added to this library. C is my best language as well as my prefered one. The only drawback in using C is the lack of many simple features found in other languages. Due to this, I decided to add common functionalities needed in most programs.


## Examples & Documentation

### Immutable/Dynamic Strings

Nowdays, it is very uncommon to find a language that does not have immutable or dynamically allocated strings. In this library, strings are implemented with basic object oriented programming features. In C, object oriented programming is made possible with the use of function pointers. Though, it does come with a few drawbacks. 
The first drawback is the required inititializer function. This function must be called upon creation of the struct as without it, the function pointers will not be pointing to anything. The standard initialization of a string is shown below.
```
// Without a string
string newstring = initString("");
// With a string
string newstring = initString("This string has been initialized!");
```

The second drawback is requirement of a self argument. With the use of function pointers, you are basically just creating an alias of the normal function. Due to this, you will still need to supply the address of the struct as you normally would with the function that is being pointed to.
```
// The self pointer is just the address of the string.
newstring.print(&newstring);
```



Now with the understanding of these drawbacks, we can move on to understanding how to use the created functions.