#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) envp;
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		ft_printf("errno = %d\n", errno);
		perror("");
		// switch (errno) {
		// 	case E
		// }
	}
	else {
		close(fd);
	}
	// pid_t	pid;
	// int		retval;

	// pid = fork();
	// if (pid == -1)
	// {
	// 	perror("fork");
	// 	exit(1);
	// }
	// else if (pid == 0)
	// {
	// }
	// else
	// {
		
	// }
}