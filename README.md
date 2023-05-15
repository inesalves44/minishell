# Minishell (42 - lvl 3)

## 1.Overview

Minishell is a project of the common core in school 42. This project was made in collaboration with [Heitor](https://github.com/HeitorMP).

It's objective is to create a simple Unix shell! 
A Unix shell is a command-line interface that allows users to interact with the operating system by executing commands. It serves as a bridge between the user and the kernel of the operating system. Minishell aims to replicate some of the basic functionalities of a Unix shell, providing a simplified version of the command-line interface.

## 2. Rules
These are the features needed to implement in the minishell process:

1. Command Line Interface: Implement a prompt that accepts user input and displays the shell's output.

2. Built-in Commands: Implement essential built-in commands such as `cd`, `echo`, `pwd`, `export`, `unset`, and `env`. These commands should be executed directly within the shell.

3. External Commands: execute shell commands directly in the program.

4. Handle `<`, `>`, `>>`,`<<`.

5. Pipes: Implement the ability to chain commands together using pipes (`|`).

6. Environment Variables: Implement functionalities to manage environment variables, including setting, unsetting, and displaying them.

7. Signal Handling: Handle signals like `Ctrl-C` (SIGINT) and `Ctrl-D` (EOF)  and `Ctrl-\` to provide a proper termination of processes and enable an interactive experience.

8. Error Handling: Implement error handling to display appropriate error messages for invalid commands or other errors that may occur during execution.

## 3. The Project
To implement this project well we needed to create a few key elements: a lexer, a parser, an expander, a treatement for redirection and for commands.

### 3.1 The Lexer
The lexer plays a crucial role in parsing the received string by separating it into tokens for future use. In our implementation, we utilize a doubly linked list as our lexer, effectively dividing the string into tokens.

It's important to note that before the separation process, we clean the string by handling quotes. Our approach involves identifying the first quote encountered and searching for its closing counterpart from the end of the string to the beginning. This ensures proper handling of quoted sections within the input.

### 3.2 The Parser
With the lexer we can finally create the parser. The parser is very important for the execution of the commands in shell! 

Our parser is an Abstract Syntax tree, being created this way:
EXEMPLO COM IMAGEM

### 3.3 The Expander


## Make Commands
```
make all - creates executable minishell
make clean - cleans the objects
make fclean - clean executable and any library, also runs clean
make re - runs clean and fclean and then runs all to create the executable
 ```
