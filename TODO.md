# Project checklist

## Development

Check the following for leaks (run with `valgrind --leak-check=full --show-leak-kinds=all`):

- `./pipex tests/in/basic.txt "cat -e" "wc -l" tests/out/outfile.txt` (both files exist)
- `./pipex tests/infiles/basic.txt "cat -e" "wc -l" tests/out/outfile.txt` (infile doesn't exist)
- `./pipex tests/in/basic.txt "cat -e" "wc -l" tests/outfiles/outfile.txt` (outfile doesn't exist)
- `./pipex tests/infiles/basic.txt "cat -e" "wc -l" tests/outfiles/outfile.txt` (neither file exists)

## Full commands to copy:

- `valgrind --leak-check=full --show-leak-kinds=all ./pipex tests/in/basic.txt "cat -e" "wc -l" tests/out/outfile.txt`
- `valgrind --leak-check=full --show-leak-kinds=all ./pipex tests/infiles/basic.txt "cat -e" "wc -l" tests/out/outfile.txt`
- `valgrind --leak-check=full --show-leak-kinds=all ./pipex tests/in/basic.txt "cat -e" "wc -l" tests/outfiles/outfile.txt`
- `valgrind --leak-check=full --show-leak-kinds=all ./pipex tests/infiles/basic.txt "cat -e" "wc -l" tests/outfiles/outfile.txt`

## Cleanup

- Check if proper data types are being used (e.g. pid_t)
- Do norminette
- Remove TODO.md and NOTES.md
- Remove tests? (or at least: 
    - remove getpid from fork, 
    - run each file,
    - check files and norminette).