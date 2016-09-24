Minish
======

Shell-like for unix operating system, developped in C language.

Minish allows the execution of system commands:
- tail
- head
- ...
depending on your available commands.

It's also possible to execute some Minish specifics commands:
- history : display history
- cd : change direct
- exit : exit minish shell
- 
Minish can redirect stdout and sterr flow using well-known syntax:
- > : erase and redirect stdout to file
- >> : append stdout to file
- 2> : erase and redirect stderr to file
- 2>> : append stderr to file

Compilation
======
Minish is included with a Makefile so you just have to be in the minish source directory
path should be something like this : 
>$ $PWD
xxx/Minish/src

and run make command :
>$ make

If the build is successful an executable called minish should be present in the directory.

Execution
======
In your favorite command line interpreter just run

>$ ./minish


Examples
======
- find . -name "file.c" | xargs grep "#include" > found.txt


