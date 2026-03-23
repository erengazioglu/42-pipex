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

Program steps:

**Parent:**  
- check if argc is good
- try opening first and last argvs
- for each other argument:
    - create a pipe
    - fork the process
    - crash if pid == -1
    - run the child process (they will duplicate fds)
- close own fds
- wait for all the children to finish
- then quit cleanly
- check if argc is good

**Child:**  
- close stdin & stdout
- dup & close parent fds to 0 and 1 (stdin and stdout)
    - if first child, use fd[2] for input (file read)
    - if last child, use fd[3] for outfile
- split its arguments (first word of argument is program, the following are its args)
- launch the command directly (do you need to read? how does execve work?)


## Instructions

### Compilation

_(More on this later.)_


### Integration

_(More on this later.)_


### Testing

_(More on this later.)_


## Resources

- **Manual entries:**
    - `man execve`
    - `man pipe`
    - `man 3 perror`
    - `man 3 write`
    - `man access`
- The Linux Programming Interface (book).
- [Beej's Guide to IPC](https://beej.us/guide/bgipc/html/split/).
- **Google & Forums:** Heavy use of Google searches, often leading to Stack Overflow and similar forums.
    - This beautiful [StackOverflow thread](https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators) in particular helped me get started.
- **AI:**
    - Helped me find _Beej's guide to IPC_ and _The Linux Programming Interface_ (above).
- **Fellow 42 students:**
    - Shout out to _sseo_ and _amguinam_ for taking the time to teaching me key concepts!
















































```c

fd[4];
fd[2] = open(fichier a lire)
fd[3] = open(fichier a ecrire)
fd 0, 1 = pipe
fd 2, 3 fichiers
child: 
    close stdin stdout
    dup fd0 -> 0 , fd1 -> 1
    prends les args
    split pour avoir args[0] ("ls -l")
    



```