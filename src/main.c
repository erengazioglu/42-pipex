/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:31:19 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/21 03:27:38 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	pid;
	int	fds[4];
	int	status;
	int	i;

	(void) envp;
	check_args(argc, argv, fds);
	i = 1;
	while (i < argc - 2)
	{
		pipe(fds);
		pid = fork();
		if (pid == -1)
			crash("forking");
		if (pid == 0)
			child_process(argc, fds, i);
	}
	close_all(fds);
	i = 1;
	while (i++ < argc - 2)
		wait(&status);
	ft_printf("I'm the parent.\n");
}
