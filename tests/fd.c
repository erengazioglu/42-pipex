/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:22:47 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/23 10:36:29 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/stat.h>

int	crash(char *s)
{
	if (s && *s)
		perror(s);
	exit(EXIT_FAILURE);
}

void	copy(int *fd, char *buf)
{
	buf = get_next_line(fd[0]);
	if (!buf)
		crash("Reading from file");
	while (buf)
	{
		if (write(fd[1], buf, ft_strlen(buf)) != (ssize_t) ft_strlen(buf))
			crash("Writing to file");
		free(buf);
		buf = get_next_line(fd[0]);
	}
}

int	main(int argc, char **argv)
{
	int		fd[2];
	int		flags[2];
	
	if (argc != 3)
	{
		errno = EINVAL;
		crash(NULL);
	}
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
		crash("Opening file to read");
	
	flags[0] = O_CREAT | O_WRONLY | O_TRUNC;
	flags[1] = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	fd[1] = open(argv[2], flags[0], flags[1]);
	if (fd[1] == -1)
		crash("Opening file to write");
	if (close(fd[0]) == -1)
		crash("Closing input file");
	if (close(fd[1]) == -1)
		crash("Closing output file");
	return (EXIT_SUCCESS);
}
