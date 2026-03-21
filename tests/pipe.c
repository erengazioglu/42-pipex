/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 00:11:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/21 00:54:22 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int crash(char *s)
{
	if (s && *s)
		perror(s);
	exit(EXIT_FAILURE);
}

int main(void)
{
	int	pid;
	int	fds[2];
	char buffer[30];
	int	status;

	pipe(fds);	// e.g. 5 = pipe input, 6 = pipe output
	pid = fork();
	if (pid == -1)
		crash("fork 1");
	if (!pid)
	{
		// every child must have 2 fds only.
		close(fds[0]);		// close read end of pipe	(total fds: 3)
		close(1);			// 0 = stdin, 1 = stdout	(total fds: 2)
		dup2(fds[1], 1);	// remap pipe to stdout		(total fds: 3)
		close(fds[1]);		//							(total fds: 2)
		write(1, "hey (I'm from 1)\n", 18);
		exit(EXIT_SUCCESS);
	}
	pid = fork();
	if (pid == -1)
		crash("fork 2");
	if (!pid)
	{
		close(fds[1]);
		close(0);
		dup2(fds[0], 0);
		close(fds[0]);
		sleep(1);
		read(0, buffer, 18);
		write(1, buffer, 18);
		sleep(1);
		write(1, "hello (I'm from 2)\n", 20);
		exit(EXIT_SUCCESS);
	}
	close(fds[0]);
	close(fds[1]);
	wait(&status);
	wait(&status);
	sleep(1);
	ft_printf("I'm parent.\n");
}
