/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 20:11:48 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/23 22:48:47 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**list;
	(void) argc;
	(void) argv;

	while (*envp)
	{
		if (ft_str_startswith(*envp, "PATH="))
		{
			list = ft_split(*envp + 5, ':');
			break;
		}
		envp++;
	}
	while (*list)
		ft_printf("%s\n", *list++);
}
