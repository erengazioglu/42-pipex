# pipex

_This project has been created as part of the 42 curriculum by egaziogl._

## Description

An exercise program in C that replicates the functionality of pipes in UNIX— specifically the following syntax: `< file1 cmd1 | cmd2 > file`

### Requirements

Program execution:  
`./pipex file1 cmd1 cmd2 file2`

External functions allowed:
- Memory allocation functions (`malloc, free`),
- Error printing (`perror, strerror`),
- I/O (`read, write, access, dup, dup2, unlink`),
- Process execution (`execve, exit, fork, pipe`),
- Process execution order control (`wait, waitpid`),
- `ft_printf`,
- `libft`.

Bonus requirements:
- Handle multiple pipes,
- Support `<<` and `>>` (if first parameter is "here_doc").

### The challenge

_(More on this later.)_


### Implementation

_(More on this later.)_


## Instructions

### Compilation

_(More on this later.)_


### Integration

_(More on this later.)_


### Testing

_(More on this later.)_


## Resources

- **Manual entries:**
    - `man perror`,
    - `man execve`,
    - `man pipe`.
- **Google & Forums:** Heavy use of Google searches, often leading to Stack Overflow and similar forums.
    - This beautiful [StackOverflow thread](https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators) in particular helped me get started.
- **AI:** _(More on this later.)_
- **Fellow 42 students:** As always, conversations with peers are the most valuable resource.
- https://beej.us/guide/bgipc/html/split/intro.html#intro

dup2 execve


valgrind --track-fds=yes --trace-children=yes
gdb for child processes
gdb --args 
set detach-on-fork off
b main etc etc
layout src
info inferiors
inferior #

protect dup2 like malloc

https://www.amazon.com/exec/obidos/ISBN=0201563177/wrichardstevensA/
https://linuxcommand.org/tlcl.php
