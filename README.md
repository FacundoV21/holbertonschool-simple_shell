# C - Simple Shell
## A customised simple UNIX command interpreter
***
## Table of Contents
1. [Introduction](#introduction)
2. [File Descriptions](#file-descriptions)
   * [shell.h](#shellh)
   * [main.c](#mainc)
   * [parse.c](#parsec)
   * [path.c](#pathc)
   * [execute.c](#executec)
3. [Basic Usage](#basic-usage)
4. [Features](#features)
5. [Program Flow](#program-flow)
6. [Edge and Special Cases](#edge-and-special-cases)
7. [Debugging and Testing](#debugging-and-testing)
8. [Potential Pitfalls](#potential-pitfalls)
9. [Scenarios that Might Cause the Program to Crash](#scenarios-that-might-cause-the-program-to-crash)
10. [Authors](#authors)
***
## Introduction
Simple Shell is a basic shell program that provides functionalities similar to traditional Unix shells. You can use it to run commands either by specifying their full paths, relative paths or by relying on the PATH environment variable. This shell handles command execution, provides feedback for errors and ensures proper memory management.
***
## File Descriptions
1. `shell.h`: This is the header file containing the necessary libraries, macro definitions and function prototypes required for our shell. It also has the structure definition for the linked list that holds directories from the PATH environment variable.
2. `main.c`: Contains the main loop of our shell program. It constantly waits for user input, processes that input and executes the corresponding commands.
3. `parse.c`: Contains functions that tokenise the user's input.
4. `path.c`: This file contains several functions related to managing and searching the PATH:
* `_getenv`: Retrieves the value of an environment variable.
* `parse_path`: Breaks down the PATH environment variable into a linked list of directories.
* `search_path`: Searches for an executable command in the directories listed in PATH.
* `free_path_list`: Frees the memory occupied by the linked list holding the PATH directories.
Once we have our commands tokenised, we need to determine their path. This makes it essential to introduce path-related operations after parsing.
5. `execute.c`: Functions in this file are responsible for the execution of commands:
* `direct_execute`: Executes commands that start with '/' or '.' directly without searching in PATH.
* `path_execute`: Searches for a command in the PATH and then executes it.
* `execute_command`: Checks how a command should be executed (either directly or through PATH) and then does so.
With the parsed tokens and determined paths, we finally execute the command.
***
## Basic Usage
**1. Compile the shell program:**
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
**2. Running:**
* After compilation, start the shell:
```bash
./hsh
```
**3. Using the Shell:**
Example:
```bash
#cisfun$ ls -l
```


**4. Exiting:**
CTRL+D or typing exit and pressing enter.
***
## Features
* Simple and intuitive user interface.
* Executes commands directly if given a full or relative path.
* Searches for commands in directories listed in the PATH environment variable.
* Displays errors if a command is not found or if there's a memory allocation issue.
* Proper memory management to avoid memory leaks.
***
## Program Flow
1. The shell starts and waits for user input.
2. When input is received, the shell tokenizes the input into commands and arguments.
3. If the command starts with '/' or '.', the shell tries to execute it directly.
4. If the command doesn't start with the characters mentioned at the previous stage, the shell searches for the command in the system's PATH directories.
5. The command is executed, and the shell waits for more user input.
6. If the user types the exit command or sends an EOF character (with CTRL + D), the shell terminates.
***
## Edge and Special Cases
**1. Empty Input:**
If a user simply presses enter without typing a command, the shell should handle this smoothly and present the user with another prompt.
**2. Command Not Found:**
If the user types in a command that isn't found in any of the directories listed in the PATH, the shell should return an error message, e.g., command not found.
**3. Permissions:**
If the command exists but the user doesn't have the right permissions to execute it, an appropriate error should be displayed.
**Invalid Arguments:**
If a command is executed with incorrect arguments, the command itself should display its error.
***
## Debugging and Testing
***
## Potential Pitfalls
***
## Scenarios that Might Cause the Program to Crash
***
## Authors