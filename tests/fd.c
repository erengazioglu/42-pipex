/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:22:47 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/24 15:28:41 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/stat.h>

/*
Launch this with 2 arguments:
tests/fd tests/files/infile tests/files/outfile

Examples:
tests/fd tes
*/

int	crash(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	copy(int *fd)
{
	char	buf[60];
	int		bytes[2];

	bytes[0] = read(fd[0], buf, 60);
	while (bytes[0] > 0)
	{
		bytes[1] = write(fd[1], buf, bytes[0]);
		if (bytes[1] == -1)
			crash("writing to file");
		bytes[0] = read(fd[0], buf, 60);
	}
	if (bytes[0] == -1)
		crash("reading from file");
}

int	main(int argc, char **argv)
{
	int		fd[2];
	
	if (argc != 3)
	{
		errno = EINVAL;
		crash(NULL);
	}
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
		crash("Opening file to read");
	fd[1] = open(argv[2], 
		O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
	);	
	if (fd[1] == -1)
		crash("Opening file to write");
	copy(fd);
	if (close(fd[0]) == -1)
		crash("Closing input file");
	if (close(fd[1]) == -1)
		crash("Closing output file");
	return (EXIT_SUCCESS);
}
