/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:28:22 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/25 10:43:47 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	redirect(t_state *state, int n)
{
	close(0);
	close(1);
	if (n == 1)
		dup2(state->fd[2], 0);
	else
		dup2(state->fd[0], 0);
	if (n == state->argc - 3)
		dup2(state->fd[3], 1);
	else
		dup2(state->fd[1], 1);
}

static char	**extract_paths(t_state *state)
{
	char	**paths;
	int		i;

	ft_printf("we're extracting paths\n");
	paths = NULL;
	i = 0;
	while (state->envp[i])
	{
		if (ft_str_startswith(state->envp[i], "PATH="))
		{
			ft_printf("found PATH variable\n");
			paths = ft_split(state->envp[i] + 5, ':');
			break;
		}
		i++;
		if (!state->envp[i])
			crash("path loop end");
	}
	i = 0;
	while (paths[i])
	{
		ft_printf("path %d: %s\n", i, paths[i]);
		paths[i] = ft_pathjoin(paths[i], state->child_args[0], true);
		ft_printf("it became %s\n", paths[i]);
		i++;
	}
	return (paths);
}

void	child_process(t_state *state, int n) // 1, 2
{
	char	**paths;
	char	**args;
	
	args = ft_split(state->argv[n + 1], ' ');
	if (!args)
		crash("ft_split on state->argv");
	sleep(n);
	// ft_printf("%s\n%s\n", *(args), *(state->envp + 1));
	redirect(state, n);
	if (ft_strchr(*args, '/'))
	{
		ft_printf("executing %s\n", *args);
		execve(*args, args, state->envp);
	}
	paths = extract_paths(state);
	ft_printf("%s is one path\n", *paths);
	for (int i = 0; paths[i]; i++)
	{
		ft_printf("testing path %s\n", paths[i]);
		execve(paths[i], args, state->envp);
	}
	crash("child execve");
}
