# MKS65C-shell
Bill Ni

## What can it do
* Change directory
* Execute commands
* Exit
  
## Functions

* strip
  * takes off whitespace surrounding string
  * takes a char ptr
  * returns char ptr

* pargs
  * splits up a char ptr into a char ** by a delimiter
  * takes a char ptr to break up and a char ptr as a delimiter
  * returns an array of char ptrs

* print_arr
  * prints an array of char ptrs
  * takes a char ptr
  * returns nothing

* exec
  * distinguishes between a standard command/command that takes stdin/command that makes stdout/commands that pipe
  * forks and execs commands
  * takes a char ptr
  * returns nothing

* prompt
  * prints command prompt
  * takes nothing
  * returns nothing

* readr
  * reads in line from command prompt
  * takes nothing
  * returns an array of char ptrs
