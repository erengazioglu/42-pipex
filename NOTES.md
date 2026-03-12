# NOTES

## Operators

**`|` (pipe) takes the output of the command on the left and feeds it as an input to the command on the right.** For example, `ls -l | wc -l` will return the number of files listed.

**`<` feeds the contents of a file to a command.** The following two are the same: `wc -l < hello.txt` and `< hello.txt wc -l`.  

**`>` takes the output of a command and writes it to a file.** Unlike `>>`, it will truncate the file. Important detail: it will open and truncate the file _before the program starts running._ So as soon as you run the command, even if the program does nothing, the contents of the file will be lost forever.