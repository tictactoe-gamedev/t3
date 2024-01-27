# Coding Standards

### General Naming Approach
Always start from the widest scope, so others can look for it easily.    
A good example is creating components. Each component in T3 starts with
`T3_Component_` and the rest is the components own name like `Camera` .
So, any dev looking for available components can easily search starting 
with `T3_Component` to find `T3_Component_Camera`

### Method Names
Methods should be named in this way `Domain_(Struct or Module)_ThingItDoes`    
i.e `T3_List_AddSafe` or `T3_Entity_AddComponent` . 
Long method names are not a bad thing. Avoid using weird abbreviations please. It's common to have
methods, which is exposed in headers but shouldn't be used. You should put `INTERNAL_` as a prefix
like `INTERNAL_T3_Entity_Something()`

### Struct Names
Structs should have naming like Domain_Struct. i.e `T3_List` or `T3_Component_Position`

### Argument Naming
Argument names should be lowerCamelCase

### Enum Naming
Please don't go mad with enum values like E_LOGGING_LEVEL. Instead of it, give your enum type a good
name (T3_Logging_Level) and use shorter enum values (Warning) 

### File Names
`lower-case-with-dash`

### Macros
Macros should be all upper case with underscore. 

### File/Folder structure
If something will be a part of the core, you should put its source file
into `core/source` and its header to `core/header` . If you have some common
domain, create a directory for them. Let's say you'll implement abstract data
types for core. You have a source for linked_list, list, binary_tree, then you
can create a directory like `core/source/data_structures`. But, if you think they
have somewhat related things in that level, then they should have a **single header**
so we can avoid complexity. A header file like `data_structures.h` should include
any exposed method for any kind of data structure.

