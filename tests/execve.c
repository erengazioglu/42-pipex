/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:04:05 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/23 14:08:17 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/stat.h>

int crash(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	check_args(int argc, char **argv, int *fds)
{
	if (argc != 4)
	{
		errno = EINVAL;
		crash("Arg check");
	}
	fds[0] = open(argv[1], O_RDONLY);
	if (fds[0] == -1)
		crash("Open file (read)");
	fds[1] = open(
		argv[argc - 1], 
		O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
	);
	if (fds[1] == -1)
	{
		close(fds[0]);
		crash("Open file (write)");
	}
}

void	redirect(int argc, int *fds, int i)
{
	(void) i;
	(void) argc;
	close(0);
	close(1);
	dup2(fds[0], 0);
	dup2(fds[1], 1);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	char	**command;

	check_args(argc, argv, fd);
	pid = fork();
	if (pid == -1)
		crash("forking");
	if (pid == 0)
	{
		redirect(argc, fd, 0);
		command = ft_split(argv[2], ' ');
		if (!execve(*command, command + 1, envp))
			crash("exec");
	}
	close(fd[0]);
	close(fd[1]);
}
