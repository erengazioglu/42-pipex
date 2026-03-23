/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 02:25:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/23 12:42:20 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int crash(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	check_args(int argc, char **argv, int *fds)
{
	if (argc < 5)
	{
		errno = EINVAL;
		crash("Arg check");
	}
	fds[2] = open(argv[1], O_RDONLY);
	if (fds[2] == -1)
		crash("Open file (read)");
	fds[3] = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	if (fds[3] == -1)
	{
		close(fds[2]);
		crash("Open file (write)");
	}
}

void	redirect(int argc, int *fds, int i)
{
	close(0);
	close(1);
	if (i == 0)
		dup2(fds[2], 0);
	else
		dup2(fds[0], 0);
	if (i == argc - 2)
		dup2(fds[3], 1);
	else
		dup2(fds[1], 0);
}

void	child_process(int argc, char *envp, int *fds, int i)
{
	redirect(argc, fds, i);
	// execve();
	sleep(1);
	ft_printf("I'm child %d\n", i);
	exit(EXIT_SUCCESS);
}

void	close_all(int *fds)
{
	close(fds[0]);
	close(fds[1]);
	close(fds[2]);
	close(fds[3]);
}

// char	*read_all(int fd, int bufsiz)
// {
// 	int		bytes_read;
// 	char	*buffer;
// 	char	*result;

// 	buffer = ft_calloc(12, 1);
// 	if (!buffer)
// 		return (NULL);
// 	bytes_read = read(fd, buffer, bufsiz);
// 	result = ft_calloc(12, 1);
// 	if (!result)
// 		return (free(buffer), NULL);
// 	ft_strlcpy(result, buffer, bufsiz);
// 	while (bytes_read)
// 	{
// 		result = ft_strnjoin(result, buffer, bytes_read, true);
// 		bytes_read = read(fd, buffer, bufsiz);
// 	}
// 	return result;
// }
