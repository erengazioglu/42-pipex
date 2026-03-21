/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 00:11:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/21 02:14:15 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int crash(char *s)
{
	if (s && *s)
		perror(s);
	exit(EXIT_FAILURE);
}

void	child1(int *fds)
{
	close(fds[0]);
	close(1);
	dup2(fds[1], 1);
	close(fds[1]);
	write(1, "hey (I'm from 1)\n", 18);
	exit(EXIT_SUCCESS);
}

void	child2(int *fds)
{
	char buffer[30];

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

int main(void)
{
	int	pid;
	int	fds[2];
	int	status;

	pipe(fds);	// e.g. 5 = pipe input, 6 = pipe output
	pid = fork();
	if (pid == -1)
		crash("fork 1");
	if (!pid)
		child1(fds);
	pid = fork();
	if (pid == -1)
		crash("fork 2");
	if (!pid)
		child2(fds);
	close(fds[0]);
	close(fds[1]);
	wait(&status);
	wait(&status);
	sleep(1);
	ft_printf("I'm parent.\n");
}
