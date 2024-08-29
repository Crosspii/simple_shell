# An implementation of sh in C programming language

## Overview

**Simple Shell** - is a ALX project. The task is to write a simple UNIX command interpreter.

Table of contents
=================

<!--ts-->
   * [Overview](#overview)
   * [Table of contents](#table-of-contents)
   * [General Requirements](#requirements)
   * [Authorized functions and macros](#list-of-allowed-functions-and-system-calls)
   * [Compilation](#compilation)
   * [Tasks](#tasks)
   * [Installation](#installation)
   * [Examples](#examples)
   * [Authors](#authors)
<!--te-->


*************************************************************************

## Requirements
### General

  - Allowed editors: vi, vim, emacs
  - All your files will be compiled on Ubuntu 14.04 LTS
  - Your programs and functions will be compiled with gcc 4.8.4 using the flags `-Wall` `-Werror` `-Wextra` and `-pedantic`
  - All your files should end with a new line
  - A `README.md` file, at the root of the folder of the project is mandatory
Your code should use the `Betty` style. It will be checked using [`betty-style.pl`](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [`betty-doc.pl`](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl)
  - No more than 5 functions per file
  - All your header files should be include guarded
  - Use system calls only when you need to ([`why?`](https://www.quora.com/Why-are-system-calls-expensive-in-operating-systems))
## More Info
### Output
- Unless specified otherwise, your program __must have the exact same output__ as `sh` (`/bin/sh`) as well as the exact same error output.
- The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]` (See below)

Example of error with `sh`:
```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```
Same error with your program `hsh`:
```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```
******************************************************************************
