/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:31:19 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/26 15:16:25 by egaziogl         ###   ########.fr       */
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
		if (i != argc - 3)
			create_pipe(state);
		state->pid = fork();
		if (state->pid == -1)
			crash(state, ERR_FORK);
		if (state->pid == 0)
			child_process(state, i);
		i++;
	}
	close_fds(state);
	i = 1;
	while (i++ < argc - 2)
	{
		if (wait(&(state->exit_code)) == state->pid)
			retval = get_exit_code(state);
	}
	return (free(state), retval);
}
