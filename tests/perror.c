/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:22:44 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/17 13:22:53 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) envp;
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		ft_printf("errno  = %d\nstrerr = %s\n", errno, strerror(errno));
		perror("My custom error prefix");
	}
	else {
		close(fd);
	}
}
