/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:28:22 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/24 13:34:01 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	redirect(t_state *state, int n)
{
	close(0);
	close(1);
	if (n == 0)
		dup2(state->fds[2], 0);
	else
		dup2(state->fds[0], 0);
	if (n == state->argc - 1)
		dup2(state->fds[3], 1);
	else
		dup2(state->fds[1], 1);
}


// void	extract_args(t_state *state, int n)
// {
// 	char	**args;
// 	args = ft_split(state->argv[n + 2], ' ');
// }

char	**extract_paths(t_state *state)
{
	char	**paths;
	int		i;

	i = 0;
	ft_printf("%s\n", state->envp[i]);
	while (state->envp[i])
	{

		if (ft_str_startswith(state->envp[i], "PATH="))
		{
			paths = ft_split(state->envp[i] + 5, ':');
			break;
		}
		i++;
	}
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strnjoin(paths[i], state->child_args[0], 5, true);
		i++;
	}
	return (paths);
}

void	child_process(t_state *state, int n)
{
	// char	**paths;

	// ft_printf("I'm running lol\n");
	redirect(state, n);
	ft_printf("something\n");
	// state->child_args = ft_split(state->argv[n + 2], ' ');
	// paths = extract_paths(state);
	// while (*paths)
	// {
	// 	// ft_printf("%s\n", *paths++);
	// }
	close(0);
	close(1);
	// execve(*args, args + 1, state->envp);
	// sleep(1);
	// crash("child ");
}
