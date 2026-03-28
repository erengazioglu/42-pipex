/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 02:25:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/28 13:14:53 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_strlist(char **list)
{
	for (int i = 0; list[i]; i++)
		free(list[i]);
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
