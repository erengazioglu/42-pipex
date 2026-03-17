/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:31:19 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/17 10:51:57 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <errno.h>

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) envp;
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		ft_printf("errno = %d\n", errno);
		// switch (errno) {
		// 	case E
		// }
	}
	else {
		close(fd);
	}
	// pid_t	pid;
	// int		retval;

	// pid = fork();
	// if (pid == -1)
	// {
	// 	perror("fork");
	// 	exit(1);
	// }
	// else if (pid == 0)
	// {
	// }
	// else
	// {
		
	// }
}