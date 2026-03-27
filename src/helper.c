/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 02:25:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/27 16:07:18 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_strlist(char **list)
{
	for (int i = 0; list[i]; i++)
		free(list[i]);
	free(list);
}

t_state	*init_state(int argc, char **argv, char **envp)
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

void	close_fds(t_state *state, bool all)
{
	close(state->fd[0]);
	close(state->fd[1]);
	if (all)
		close(state->fd[2]);
}

void	create_pipe(t_state *state, int n)
{
	int	fd[2];

	if (n == state->argc - 3)
		return;
	if (pipe(fd) == -1)
		crash(state, ERR_PIPE);
	state->fd[0] = fd[0];
	state->fd[1] = fd[1];
}

char	*ft_pathjoin(char *s1, char *s2, bool free_s1)
{
	char	*result;
	char	*result_base;
	char	*s1_base;

	if (ft_strchr(s2, '/'))
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!result)
	{
		if (free_s1)
			free(s1);
		return (NULL);
	}
	result_base = result;
	s1_base = s1;
	while (*s1)
		*(result++) = *(s1++);
	*(result++) = '/';
	while (*s2)
		*(result++) = *(s2++);
	*result = '\0';
	if (free_s1)
		free(s1_base);
	return (result_base);
}
