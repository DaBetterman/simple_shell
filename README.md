# Simple Shell Project

## Overview
This is a simple shell project that allows you to execute basic commands. Below, you'll find some information on how to use the shell and understand its output.

## Usage
0. **Compilation:** Using `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh` to compile all the files.

```
ebrahim@ebrahim-desktop:~/medium-shell/simple_shell$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
ebrahim@ebrahim-desktop:~/medium-shell/simple_shell$ 
```

1. **Run the Shell:** To start the shell, run the executable `hsh` in your terminal.
```
ebrahim@ebrahim-desktop:~/medium-shell/simple_shell$ ./hsh
😃:~$ 
```

2. **Execute Commands:** You can execute various commands like `ls`, `echo`, `printenv` or `env` within the shell.

```
😃:~$ ls
error.c  execution.c  exit.c  hsh  main.c  path.c  prompt.c  shell.h  string1.c  string2.c  white_space.c
😃:~$ 
```


3. **Listing Files:** You can use the `ls -la` command to list detailed information about files.
```
😃:~$ ls -la
total 68
drwx------ 2 ebrahim ebrahim  4096 Nov  5 10:15 .
drwxrwxr-x 4 ebrahim ebrahim  4096 Nov  4 09:54 ..
-rw-rw-r-- 1 ebrahim ebrahim  1439 Nov  9 21:23 error.c
-rw-rw-r-- 1 ebrahim ebrahim   639 Nov  9 21:14 execution.c
-rw-rw-r-- 1 ebrahim ebrahim   264 Nov 11 14:36 exit.c
-rwxrwxr-x 1 ebrahim ebrahim 17320 Nov 10 10:15 hsh
-rw-rw-r-- 1 ebrahim ebrahim   294 Nov  4 11:09 main.c
-rw-rw-r-- 1 ebrahim ebrahim   456 Nov  9 21:01 path.c
-rw-rw-r-- 1 ebrahim ebrahim  1123 Nov  4 10:15 prompt.c
-rw-rw-r-- 1 ebrahim ebrahim   792 Nov  4 10:05 shell.h
-rw-rw-r-- 1 ebrahim ebrahim  1528 Nov  6 10:09 string1.c
-rw-rw-r-- 1 ebrahim ebrahim  1009 Nov  6 10:11 string2.c
-rw-rw-r-- 1 ebrahim ebrahim   430 Nov  9 15:30 white_space.c
😃:~$ 
```

4. **Exiting the Shell:** To exit the shell, type `exit`.
```
😃:~$ exit
ebrahim@ebrahim-desktop:~/medium-shell/simple_shell$
```

5. **Echo command:** You can execute the `echo` command to display your argument on the stdout.

```
😃:~$ echo "love"    
"love"
😃:~$ echo "$USER"
"$USER"
😃:~$ 
```

6. **Printing the environment:** Insert `env` or `printenv` to display the systems environment.
```
😃:~$ env
SHELL=/bin/bash
SESSION_MANAGER=local/ebrahim-desktop:@/tmp/.ICE-unix/2171,unix/ebrahim-desktop:/tmp/.ICE-unix/2171
QT_ACCESSIBILITY=1
COLORTERM=truecolor

...

PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
GDMSESSION=cinnamon
ORIGINAL_XDG_CURRENT_DESKTOP=X-Cinnamon
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
TERM_PROGRAM=vscode
_=./hsh
😃:~$ 
```

7. **Cancel running program:** By pressing `ctrl + c` you will stop the current running program and start on a new line.
```
😃:~$ ^C
😟:~$ ^C
😟:~$ ^C
😟:~$ ^C
😟:~$ 
😃:~$ 
```




## Notes
- The shell supports basic commands like `ls`, `echo`, `printenv` and `env`.
- You can list files with detailed information using `ls -la`.
- There are more commands that can be executed, try it out and see...

Feel free to explore and use this simple shell for your command-line needs! If you have any questions, refer to the code or feel free to reach out. Happy coding!

## Author

- *Ebrahim Rhode* <1ebrahimr@gmail.com>

