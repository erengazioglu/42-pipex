/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:39:18 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/21 00:10:07 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/stat.h>

int	crash(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	init_pid(int *pid)
{
	pid = malloc(3 * sizeof(pid_t));
	pid[2] = 0;
}

int	pid_len(int *pid)
{
	int	i;

	i = 0;
	while (*pid++)
		i++;
	return (i);
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
		if (pid == 0)
		{
			sleep(i);
			ft_printf("I'm child %d\n", i);
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
