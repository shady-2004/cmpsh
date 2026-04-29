# cmpsh Shell
A shell is a command-line interface that allows users to interact with the operating system by entering commands. It acts as an intermediary between the user and the operating system's services, interpreting user commands and executing them. Shells can execute built-in commands, run external programs, and manage processes. Common examples of shells include Bash, Zsh, and Fish. Shells can be run in an interactive mode as when you open a new terminal (it invokes `bash` without arguments) or in a non-interactive mode as when you run a script (invoking `bash` with a file path argument).

## Overview
`cmpsh` is a custom shell program written in C that provides basic shell functionality that can be run in interactive or non-interactive mode.

The shell is very simple (conceptually): it runs in a while loop, repeatedly asking for input (prints a prompt `cmpsh> `) to tell it what command to execute. It then executes that command. The loop continues indefinitely, until the user types the built-in command `exit`, at which point it exits.

## Features
### Built-in Commands

Every shell needs to support a number of built-in commands, which are functions in the shell itself, not external programs. For example, the exit command needs to be implemented as a built-in command, because it exits the shell itself.

- `exit`: Exits the shell program.
- `cd <directory>`: Changes the current working directory.
- `pwd`: Prints the current working directory.
- `paths <path>...`: Overwrites the list of program search paths.
    ```sh
    cmpsh> path /bin /usr/bin
    # Add /bin and /usr/bin to the search path of the shell
    ```
    - calling `paths` with no arguments shall set path to be empty and the shell should not be able to run any programs (except built-in commands).

### External Commands
- The shell should support executing external commands (`ls -a`, `wc`, `echo hello`, ..etc) by forking a child process by calling one of the functions from the `exec` family to run the new program.
- It should first resolve the path of this program, find the executable in one of the directories specified by path and create a new process to run it.
    - Your initial shell path should contain one directory: `/bin`


### Signal Handling
- The shell should propagate signals such as `SIGINT` (Ctrl+C) and `SIGTSTP` (Ctrl+Z) to the currently running child process.
- The shell itself should not terminate when these signals are received even if no other program is running.

### Redirection
When running programs, it is useful to direct output to a file. The syntax `[process] > [file]` tells your shell to redirect the process’s standard output to a file. 
```sh
ls -la /tmp > output 
# nothing should be printed on the screen. Instead, the standard output of the ls program should be rerouted to the file output
```

### Non-interactive Mode
- The shell is given an input file of commands; in this case, the shell should not read user input (from `stdin`) but rather from this file to get the commands to execute.
- If you hit the end-of-file marker `EOF`, you should call `exit(0)` and exit gracefully.
```
Usage: bash> ./cmpsh myCmpshFile.sh
```
### Reporting Errors
There is a difference between errors that your shell catches and those that the program catches. Your shell should catch all the syntax errors specified in this project page. If the syntax of the command looks perfect, you simply run the specified program. If there are any program-related errors (e.g., invalid arguments to `ls` when you run it, for example), the shell does not have to worry about that (rather, the program will print its own error messages and exit).
- For any shell error print to `stderr` "An error has occured!".

## Helpful Functions
**Read the `man` page of each syscall for more info. (ex: `man strtok`)**
- Tokenization: `strtok()`, `strtok_r()`
- Process Management: `fork()`, `exec()`, `execv()` `wait()`, `waitpid()`
- Program Checking: `access()`
- Directory Management: `chdir()`, `getcwd()`

**Caution**
Your program may end up creating too many processes than intended due to a bug (fork bomb). To prevent your self to be locked out of the system limit the number of processes you can create by adding this line to your `.bashrc` file in your home directory.

`ulimit –u 100`

## Deliverables
1. Source code for `cmpsh`.
2. A `Makefile` to build the program.
    - Running `make` should produce an executable named `cmpsh`.
3. Documentation on how to use the shell and its features.

**Plagiarism will result in zero grade.**
