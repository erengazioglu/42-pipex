/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:28:22 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/23 17:42:42 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	redirect(t_state *state, int i)
{
	close(0);
	close(1);
	if (i == 0)
		dup2(state->fds[2], 0);
	else
		dup2(state->fds[0], 0);
	if (i == state->argc - 2)
		dup2(state->fds[3], 1);
	else
		dup2(state->fds[1], 0);
}

void	extract_args(t_state *state, int i)
{
	char	**args;
	args = ft_split(state->argv[i + 2], ' ');
}

char	*check_path(char )

void	child_process(t_state *state, int i)
{
	char	**args;

	redirect(state, i);
	args = ft_split(state->argv[i + 2], ' ');
	execve(*args, args + 1, state->envp);
	// sleep(1);
	crash("child ");
}
