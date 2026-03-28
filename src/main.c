/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:31:19 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/28 19:04:01 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	get_exit_code(t_state *state)
{
	if (WIFSIGNALED(state->exit_code))
		return (128 + WTERMSIG(state->exit_code));
	if (WIFEXITED(state->exit_code))
		return (WEXITSTATUS(state->exit_code));
	return (1);
}

static t_state	*init_state(int argc, char **argv, char **envp)
{
	t_state	*state;

	if (argc < 5)
		crash(NULL, ERR_ARGS);
	state = ft_calloc(1, sizeof(t_state));
	if (!state)
		crash(NULL, ERR_MALLOC);
	state->argc = argc;
	state->argv = argv;
	state->envp = envp;
	state->fd[0] = -2;
	state->fd[1] = -2;
	state->fd[2] = -2;
	return (state);
}

static void	create_pipe(t_state *state, int n)
{
	int	fd[2];

	if (n == state->argc - 3)
		return;
	if (pipe(fd) == -1)
		crash(state, ERR_PIPE);
	state->fd[0] = fd[0];
	state->fd[1] = fd[1];
}

static void	cleanup(t_state *state, int n)
{
	if (n == 1)
	{
		close(state->fd[1]);
		state->fd[2] = state->fd[0];
		state->fd[0] = -2;
	}
	else if (n < state->argc - 3)
	{
		close(state->fd[1]);
		close(state->fd[2]);
		state->fd[2] = state->fd[0];
		state->fd[0] = -2;
	}
	else
		close(state->fd[2]);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		retval;
	t_state	*state;

	state = init_state(argc, argv, envp);
	i = 1;
	while (i < argc - 2)
	{
		create_pipe(state, i);
		state->pid = fork();
		if (state->pid == -1)
			crash(state, ERR_FORK);
		if (state->pid == 0)
			child_process(state, i);
		cleanup(state, i);
		i++;
	}
	i = 1;
	while (i++ < argc - 2)
	{
		if (wait(&(state->exit_code)) == state->pid)
			retval = get_exit_code(state);
	}
	return (free(state), retval);
}
