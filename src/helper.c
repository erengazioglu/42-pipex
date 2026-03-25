/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 02:25:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/25 14:37:19 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_state	*init_state(int argc, char **argv, char **envp)
{
	t_state	*state;

	if (argc < 5)
		crash(NULL, ERR_ARGS);
	state = ft_calloc(1, sizeof(t_state));
	if (!state)
		crash(NULL, ERR_MALLOC);
	state->fd[2] = open(argv[1], O_RDONLY);
	if (state->fd[2] == -1)
		crash(state, ERR_OPENR);
	state->fd[3] = open(
		argv[argc - 1], 
		O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
	);
	if (state->fd[3] == -1)
		crash(state, ERR_OPENW);
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

void	create_pipe(t_state *state)
{
	int	fd[2];

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
