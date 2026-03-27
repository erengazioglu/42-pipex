/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:31:19 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/27 17:14:07 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	get_exit_code(t_state *state)
{
	if (WIFSIGNALED(state->exit_code))
		return (128 + WTERMSIG(state->exit_code));
	if (WIFEXITED(state->exit_code))
		return (WEXITSTATUS(state->exit_code));
	return (1);
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
		close(state->fd[1]);           // parent closes write-end
		state->fd[2] = state->fd[0];  // carry read-end forward for next child's stdin
		state->fd[1] = -2;
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
