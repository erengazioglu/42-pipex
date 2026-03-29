/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:42:11 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/29 01:51:30 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	free_list(char **list)
{
	while (*list)
		free(*(list++));
	free(list);
}

static int	skip(char const *s, char c, bool is_word)
{
	int	i;

	i = 0;
	if (is_word)
	{
		while (s[i] && s[i] != c)
			i++;
	}
	else
	{
		while (s[i] && s[i] == c)
			i++;
	}
	// ft_printf("skipping %d\n", i);
	return (i);
}

static int	count_words(char const *s, char c, bool ltrim)
{
	int	count;

	if (*s && ltrim)
		s += skip(s, c, false);
	// ft_printf("first skip\n");
	if (!(*s))
		return (0);
	s += skip(s, c, false);
	s += skip(s, c, true);
	count = 1;
	while (*s)
	{
		s += skip(s, c, false);
		if (*s)
		{
			count++;
			s += skip(s, c, true);
		}
	}
	return (count);
}

static int	pick_word(char const *s, char c, char **result, bool ltrim)
{
	int	start;
	int	len;

	start = 0;
	if (ltrim)
		start += skip(s, c, false);	
	len = start;
	while (s[len] && s[len] != c)
		len++;
	*result = ft_substr(s, start, len);
	return (len);
}

char	**ft_split(char const *s, char c, bool ltrim)
{
	char	**result;
	char	**retval;

	result = ft_calloc(count_words(s, c, ltrim) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	retval = result;
	if (ltrim && *s)
		s += skip(s, c, false);
	if (!(*s))
		return (retval);
	while (*s)
	{
		s += pick_word(s, c, result, ltrim);
		if (!(*result))
			return (free_list(retval), NULL);
		result++;
		s += skip(s, c, false);
	}
	return (retval);
}
