/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:42:11 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/28 20:53:54 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// static void	free_list(char **list)
// {
// 	while (*list)
// 		free(*(list++));
// 	free(list);
// }

static int	skip(char const *s, char c, bool is_word)
{
	int	i;

	i = 0;
	if (is_word)
	{
		while (s[i] && s[i] == c)
			i++;
	}
	else
	{
		while (s[i] && s[i] != c)
			i++;
	}
	return (++i);
}

static int	count_words(char const *s, char c, bool ltrim)
{
	int	count;

	if (*s && ltrim)
		s += skip(s, c, false);
	if (!(*s))
		return (0);
	count = 0;
	while (*s)
	{
		count++;
		s += skip(s, c, true);
		s += skip(s, c, false);
	}
	return (count);
}

// static int	pick_word(char const *s, char c, char **result)
// {
// 	int	len;

// 	len = 0;
// 	while (s[len] && s[len] != c)
// 		len++;
// 	*result = ft_substr(s, 0, len);
// 	return (len);
// }

char	**ft_split(char const *s, char c, bool ltrim)
{
	(void) ltrim;
	ft_printf("%d\n", count_words(s, c, ltrim));
	return (NULL);

	// char	**result;
	// char	**retval;

	// result = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	// if (!result)
	// 	return (NULL);
	// retval = result;
	// if (ltrim && *s)
	// 	s += trim_left(s, c);
	// while (*s)
	// {
	// 	if (*s)
	// 	{
	// 		s += pick_word(s, c, result);
	// 		if (!(*result))
	// 		{
	// 			free_list(retval);
	// 			return (NULL);
	// 		}
	// 		result++;
	// 	}
	// 	s += trim_left(s, c);
	// }
	// return (retval);
}
