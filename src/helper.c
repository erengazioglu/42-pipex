/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 02:25:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/29 16:48:03 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	dup_fd(t_state *state, int from, int to)
{
	int	fd;

	fd = dup2(from, to);
	if (fd == -1)
		crash(state, ERR_DUP2);
	return (fd);
}

void	free_strlist(char **list)
{
	int	i;

	while (list[i])
		free(list[i++]);
	free(list);
}

void	close_fds(t_state *state, bool all)
{
	close(state->fd[0]);
	close(state->fd[1]);
	if (all)
		close(state->fd[2]);
}

void	custom_err(char *left, char *right)
{
	write(2, left, ft_strlen(left));
	write(2, ": ", 2);
	write(2, right, ft_strlen(right));
	write(2, "\n", 1);
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
