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

Now, after understanding these drawbacks, we can move on to understanding how to use the precreated functions. Firstly, the most simple function is **print**. This function will print out the string along with a trailing newline. The example usage of the function is shown below.
```
newstring.print(&newstring);
```

Following print, there is also an **input** function that dynamically allocated the input. Realloc is not intended to be used in a iterative manor as it is constantly searching for free memory spaces. Due to this, a blocksize argument is used to allow for more efficient allocation. For example, if you know that you will be allocating over one kilobyte of data, a block size of one kilobyte is an efficient choice. This blocksize will reallocate an extra kilobyte when needed. An example of this is shown below.
```
// This takes user input with a blocksize of one kilobyte
newstring.input(&test, 1024);
```

**find** is another function that, as described by the name, will return the position of the first matching substring. For example, if the string is "This is a test" and the selector is "test", the returned integer will be 10.
```
newstring.find(&newstring, "test");
```

Next, we have **length** which is also pretty self explanitory. This function returns the length of the string itself by iterating through the string until a null byte is found. An example of this function is shown below.
```
newstring.length(&newstring);
```

The ability to append is also included in this library through the function **append**. As described by the name, this function will append/concatenate two strings together. If the strings initial value is "first", by concatenating " second", the result will be "first second". An example is shown below.
```
newstring.append(&newstring, " second");
```

Paired with these functions, you also have the **substr** function. This function takes two position arguments in the form of integers. The first integer is the start position of the substring and the second is the end position. An example is shown below.
```
// This is taking a substring from the string "this is a test"
newstring.substr(&newstring, 10, 14);
// This will output "test"
```

Lastly, you have **replace**. This function takes in two strings. The first string is the value that will be found and replaced. The second value is the the replacement.
```
// With the string "The word temp will be replaced" using the following command,
newstring.replace(&newstring, "temp", "replaced");
// The result will be "The word replaced will be replaced"
```