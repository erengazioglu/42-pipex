/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:39:18 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/18 20:00:22 by egaziogl         ###   ########.fr       */
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
	int	status;
	int	pid[2];
	(void) argv;
	(void) envp;
	if (argc != 2)
	{
		errno = EINVAL;
		crash(NULL);
	}
	pid[0] = fork();
	if (pid[0] == -1)
		crash("fork 1");
	pid[1] = fork();
	if (pid[1] == -1)
		crash("fork 2");
	if (!pid)
	{
		wait();
		ft_printf("I'm the parent\n");
	}
	else if (pid == pid[0])
	{
		sleep(1);
		ft_printf("I'm child 1\n");
	}
	else if (pid == pid[1])
	{
		sleep(2);
		ft_printf("I'm child 2\n");
	}
}
