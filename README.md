# pipex

_This project has been created as part of the 42 curriculum by egaziogl._

## Description

An exercise program in C that replicates the functionality of pipes in UNIX— specifically the following syntax: `< file1 cmd1 | cmd2 > file`.

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
- Handle multiple pipes (DONE),
- Support `<<` and `>>` (if first parameter is "here_doc") (SKIPPED).

### The challenge

The novelty in this project is to be able to write a program that spawns children, and have them communicate with each other through the use of pipes. 

It's an opportunity to learn about interprocess communication (IPC) and all the management that comes with it:  
- error handling,
- memory and resource management (malloc & fd),
- input/output redirection (understanding fds 0, 1, 2).

### Implementation

I'm using a "state" struct, as I did in my `so_long` project, which is a design pattern I often fall back to, especially because it helps with the restrictions of the 42 Norm (4 params per function, 25 lines per function, 5 functions per file). 

It essentially allows me to keep track of important variables (file descriptors, allocated memory...) and more importantly, **crash from wherever I want in the code by always keeping that one reference handy.** 

#### Parent process

The parent's responsibility is limited to:
- initializing the program (parsing args, initializing state object),
- creating `n-1` pipes for `n` child processes,
- spawning `n` children,
- closing the pipe ends after passing them to its children,
- waiting for all the children to finish,
- return the exit code of the last child.

#### Children

When forked, each child receives an exact duplicate of the parent's state (aside from a few exceptions outside our scope), including the file descriptors.

Each child will therefore, depending on which child it is:
- duplicate the file descriptors it needs (remapping them to 0 and 1),
- closing the ones it doesn't need,
- ft_split the respective command received in args (e.g. `"cat -e" becomes ["cat", "-e"]`),
- check if the command exists and file permissions allow its execution (`access`),
- launch `execve`.

First and last child are responsible with opening and closing the input and output files, respectively.

If the command provided does not have any "/" characters in it, the program will check the `PATH` variable, and try each path in it.

## Instructions

### Compilation

Clone the repository & run `make`.

### Use

Running:  
`./pipex <input file> <command 1 with args> <command 2 with args> <output file>`

is equivalent to:
`< <input file> <command 1 with args> | <command 2 with args> > <output file>`.

You can add more than 2 commands since I did the bonuses too!

### Testing

`valgrind --track-fds=yes ./pipex tests/in/basic.txt cat wc tests/out/basic.txt`  
This shows open fds besides the standard ones at the end of execution. It gave me a false positive once:

```
==274881== FILE DESCRIPTORS: 4 open (3 std) at exit.
==274881== Open file descriptor 5: /dev/ptmx
==274881==    <inherited from parent>
```

Named file descriptors are those that come from elsewhere, so they are safe to ignore.

You can also log for each process:
`valgrind --track-fds=yes --trace-children=yes --log-file=valgrind-%p.log ./pipex tests/in/basic.txt cat wc tests/out/basic.txt`

This kind of log will also show you open file descriptors for each log file. That's also normal, valgrind is the one managing those.

## Resources

- **Manual entries:**
    - `man execve`
    - `man pipe`
    - `man 3 perror`
    - `man 3 write`
    - `man access`
- [The Linux Programming Interface](https://man7.org/tlpi/).
- [Beej's Guide to IPC](https://beej.us/guide/bgipc/html/split/).
- **Google & Forums:** Heavy use of Google searches, often leading to Stack Overflow and similar forums.
    - This beautiful [StackOverflow thread](https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators) in particular helped me get started (especially for redirection).
- **AI:**
    - Helped me find _Beej's guide to IPC_ and _The Linux Programming Interface_ (above).
    - I ask questions related to git and debugging to AI (e.g. _git workflow for managing branches and tags, how to use valgrind for multiple processes..._).
- **Fellow 42 students:**
    - Shout out to _sseo, amguinam, nfenollo, iargence, kdonlon_ for taking the time to teaching me key concepts!
