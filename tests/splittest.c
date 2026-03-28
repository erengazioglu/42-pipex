/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splittest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:37:07 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/28 20:44:55 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv)
{
	char	**list;

	if (argc != 2)
	{
		errno = EINVAL;
		perror(NULL);
		exit(1);
	}
	list = ft_split(argv[1], ' ', false);
	// while (*list)
		// ft_printf("%s\n", *(list++));
}