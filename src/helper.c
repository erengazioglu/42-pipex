/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 02:25:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/24 16:02:03 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int crash(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

t_state	*init_state(int argc, char **argv, char **envp)
{
	t_state	*state;

	if (argc < 5)
	{
		errno = EINVAL;
		crash("Arg check");
	}
	state = ft_calloc(1, sizeof(t_state));
	state->fd[2] = open(argv[1], O_RDONLY);
	if (state->fd[2] == -1)
		crash("Open file (read)");
	state->fd[3] = open(
		argv[argc - 1], 
		O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
	);
	if (state->fd[3] == -1)
	{
		close(state->fd[2]);
		crash("Open file (write)");
	}
	state->argc = argc;
	state->argv = argv;
	state->envp = envp;
	return (state);
}

void	close_fds(t_state *state)
{
	close(state->fd[0]);
	close(state->fd[1]);
	close(state->fd[2]);
	close(state->fd[3]);
}

void	pipe_and_fork(t_state *state)
{
	int	fd[2];

	if (pipe(fd) == -1)
		crash("pipe creation");
	state->fd[0] = fd[0];
	state->fd[1] = fd[1];
	state->pid = fork();
}
