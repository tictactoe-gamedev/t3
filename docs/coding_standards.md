# Coding Standards

### Method Names
If a method name is starting with __ (2 underscores) it's for internal usage ,
and it has a macro probably that you should use instead.


### Naming
Any T3 framework related thing must have `T3_` as a prefix with underscore. 
I.e "`T3_Entity`" is a struct for ECS system. 

### Struct Naming
Use UpperCamelCase for struct elements and struct names. 

### Argument Naming
Argument names should be lowerCamelCase

### Function Names
If a function is related to a struct, it must include its struct name
as a prefix with underscore. I.e "`T3_Entity_Init()`" can be the init method name
for `T3_Entity`

### File Names
`lower-case-with-dash`