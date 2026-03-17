/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:33:49 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/17 18:08:41 by egaziogl         ###   ########.fr       */
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
	int child_pid[2];
	int child_rv;

	child_pid[0] = fork();
	if (child_pid[0] == -1)
		crash("first fork");
	else if (!child_pid[0])
		ft_printf("[CHILD1] I'm the first spawn.\n"); // execve
	else
	{
		//;
	}
	child_pid[1] = fork()


	waitpid(child_);

	return (EXIT_SUCCESS);
}
