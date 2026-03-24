/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:28:22 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/24 19:44:05 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	redirect(t_state *state, int n) // 1, 2
{
	close(0);
	close(1);
	if (n == 1)
		dup2(state->fd[2], 0);
	else
		dup2(state->fd[0], 0);
	if (n == state->argc - 3) //1 == 2, 2 == 2
		dup2(state->fd[3], 1);
	else
		dup2(state->fd[1], 1);
}

// char	**extract_paths(t_state *state)
// {
// 	char	**paths;
// 	int		i;

// 	i = 0;
// 	ft_printf("%s\n", state->envp[i]);
// 	while (state->envp[i])
// 	{

// 		if (ft_str_startswith(state->envp[i], "PATH="))
// 		{
// 			paths = ft_split(state->envp[i] + 5, ':');
// 			break;
// 		}
// 		i++;
// 		if (!state->envp[i])
// 			crash(NULL);
// 	}
// 	i = 0;
// 	while (paths[i])
// 	{
// 		paths[i] = ft_strnjoin(paths[i], state->child_args[0], 5, true);
// 		i++;
// 	}
// 	return (paths);
// }

void	child_process(t_state *state, int n) // 1, 2
{
	char	num;
	
	num = '0' + n;
	redirect(state, n);
	write(1, &num, 1);
	close(0);
	close(1);
}
