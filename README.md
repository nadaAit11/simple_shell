Simple Shell:

This is a simple UNIX command line interpreter implemented in C. The shell supports basic functionnalities and follows the specified requirements.

Output:

The shell is expected to produce the exact same output as the /bin/sh command and havethe same error output. The only diffrence is that when an error occurs, the name of the program ('argv[0]') should be equivalent to your program name (See below) :

Example of error with sh:
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$

List of Allowed Function and System Calls:

The shell can make use of the following functions and system calls:

. access
. chdir
. close
. closedir
. execve
. exit
. _exit
. fflush
. fork
. free
. getcwd
. getline
. getpid
. isatty
. kill
. malloc
. open
. opendir
. perror
. read
. readdir
. signal
. stat
. lstat
. fstat
. strtok
. wait
. waitpid
. wait3
. wait4
. write

Compilation : 

To compile the shell, use the following command : 

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

Testing :

The shell should work in both interactive and non-interactive modes. Here are some examples:

interactive mode :

$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$

non-interactive mode :

$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$

Please refer to the GitHub repository for the simple shell project for further details and code implementation.


Contributors :

. Nazih Touih
. Nada Ait Kidar
