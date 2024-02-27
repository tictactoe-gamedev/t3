# Header Name
**Header:** `#include "include/path/here.h"`


Summarize "what" this header is, "for what" it is used and "how" it does this job **briefly** .


**Important:** Table of contents should be ordered as below. By internals, we mention anything that won't be used by end user probably (something like private)

## Table Of Contents
* [Struct](#t3_somestructname)
* [Macros & Functions](#macros--functions)
    * [Some Macro](#somemacroname)
    * Some Function
* How tos
    * How to one
    * How to two

* Internals
    * Some Function
    * Another Function


## T3_SomeStructName
****
```
typedef struct T3_SomeStructName{
    int a;  
    const char* c;
    uint32 someAmbigousData;
} T3_SomeStructName;
```
* **someAmbigousData:** We will only describe variables that not so clear. (we should also avoid unclear things :) )

## Macros & Functions
***
### SomeMacroName
[[ Top ^ ]](#table-of-contents)
```
MacrosSignature(arg1, 
                arg2, 
                arg3);
```
* **arg2:** As we did in structs, we'll only explain ambiguous arguments below the method signature

Description of the function in simple terms. Make it clear and concise.

**Usage:**

```
MacrosSignature(23,"hello",abc);
```
>**Tip:** If there's something people should know about it    
>(maybe it's performance
impact or let's say, best practices)



## How to's
***

### How to one
[[ Top ^ ]](#table-of-contents)
> After following this how-to you'll be able to produce XYZ result on your project.

How to sections are really important! Please do your best to
decrease complexity and decouple the task from preliminary knowledge of another thing.
I.e if you'll explain how to use input system, try to do it with only input system
and maybe some logging. Try to avoid using sprite renderer which will add an extra
effort to user. A blockquote on top of each how to would be great.

> Another blockquote which explains what will be done on the next step.

```
some code
some code
more code
```

and continues...