/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 00:11:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/21 02:12:04 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int crash(char *s)
{
	if (s && *s)
		perror(s);
	exit(EXIT_FAILURE);
}

void	check_args(int argc, char **argv)
{
	(void) argv;
	if (argc < 2)
	{
		errno = EINVAL;
		crash(NULL);
	}
}

void	connect(int *fds, bool read, bool write)
{
	if (read)
	{
		close(0);
		dup2(fds[0], 0);
	}
	if (write)
	{
		close(1);
		dup2(fds[1], 1);
	}
}

int main(int argc, char **argv)
{
	int	pid;
	int	fds[2];
	int	status;

	check_args(argc, argv);
	for (int i = 0; i < argc - 1; i++)
	{
		pipe(fds);
		pid = fork();
		if (pid == -1)
			crash("forking");
		if (pid == 0)
		{
			connect(fds, i != 0, i != argc - 2);
			sleep(i + 1);
			ft_printf("(%d) %s\n", i, argv[i + 1]);
			exit(EXIT_SUCCESS);
		}
	}
	close(fds[0]);
	close(fds[1]);
	for (int i = 0; i < argc - 1; i++)
		wait(&status);
	sleep(1);
	ft_printf("I'm parent.\n");
}
