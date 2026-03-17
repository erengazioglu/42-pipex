# NOTES

Checklist:
- File descriptors
- pipe
- execve
- wait, waitpid
- dup2
- perror

## General info

- `init` is the first program to run after the system is booted. It runs as PID 1. All other processes are descended from `init`. It will inherit the dangling child processes if their parent dies first (and handle them heavy-handedly).

## Operators

**`|` (pipe) takes the output of the command on the left and feeds it as an input to the command on the right.** For example, `ls -l | wc -l` will return the number of files listed.

**`<` feeds the contents of a file to a command.** The following two are the same: `wc -l < hello.txt` and `< hello.txt wc -l`.  

**`>` takes the output of a command and writes it to a file.** Unlike `>>`, it will truncate the file. Important detail: it will open and truncate the file _before the program starts running._ So as soon as you run the command, even if the program does nothing, the contents of the file will be lost forever.

## pipe()

In a pipeline, all commands work concurrently as separate processes.

## File descriptors

## Child processes (fork)

**The child process will get a copy of the parent's data.** 

**The parent will wait() or waitpid() for the child to signal its exit.** It could also ignore `SIGCHLD` (`signal(SIGCHLD, SIG_IGN)`).

**fork() will return -1 if there was an issue, 0 if you are the child process, or the child's pid if you're the parent process.** 

## Waits (wait(), waitpid())

- wait will wait for any child that exits first. waitpid will wait for a specific child to exit instead.

## Errors (perror, strerror)

`perror(const char *s)`:

> Produces a message on stderr describing the last error encountered (...).

- Prefixed by the string s passed in as argument.

## Unsorted

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
