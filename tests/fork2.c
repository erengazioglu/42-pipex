/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:39:18 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/21 00:14:33 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/stat.h>

int	crash(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	pid_t	pid;
	int		count;
	(void) argv;
	(void) envp;

	if (argc < 2)
	{
		errno = EINVAL;
		crash(NULL);
	}
	count = argc - 1;
	for (int i = 0; i < count; i++)
	{
		pid = fork();
		if (pid == -1)
			crash("forking");
		if (pid == 0)
		{
			sleep(i);
			ft_printf("I'm child %d\n", getpid());
			exit(EXIT_SUCCESS);
		}
	}
	if (pid)
	{
		for (int i = 0; i < count; i++)
			wait(&status);
		sleep(1);
		ft_printf("I'm the parent.\n");
	}
}
