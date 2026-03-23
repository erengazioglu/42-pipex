/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 10:07:36 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/22 20:19:44 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int crash(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	child1(int *fds)
{
	
	close(fds[0]);
	close(1);
	dup2(fds[1], 1);
	close(fds[1]);
	write(1, "hey (I'm from 1)\n", 18);
	sleep(1);
	write(1, "I'm not done yet\n", 18);
	sleep(1);
	write(1, "I'm done now!\n", 16);
	exit(EXIT_SUCCESS);
}

char	*read_all(int fd, int bufsiz)
{
	int		bytes_read;
	char	*buffer;
	char	*result;

	buffer = ft_calloc(12, 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, bufsiz);
	result = ft_calloc(12, 1);
	if (!result)
		return (free(buffer), NULL);
	ft_strlcpy(result, buffer, bufsiz);
	while (bytes_read)
	{
		result = ft_strnjoin(result, buffer, bytes_read, true);
		bytes_read = read(fd, buffer, bufsiz);
	}
	return result;
}

void	child2(int *fds)
{
	char	*input;

	close(fds[1]);
	close(0);
	dup2(fds[0], 0);
	close(fds[0]);
	sleep(2);
	input = read_all(0, 60);
	ft_printf("I'm from 2:\n%s\n", input);
	free(input);
	// write(1, "%s (I'm from 2)\n", 20);
	sleep(1);
	exit(EXIT_SUCCESS);
}

int main(void)
{
	int	pid;
	int	fds[2];
	int	status;

	pipe(fds);	
	pid = fork();
	if (pid == -1)
		crash("fork 1");
	if (!pid)
		child1(fds);
	pid = fork();
	if (pid == -1)
		crash("fork 2");
	if (!pid)
		child2(fds);
	close(fds[0]);
	close(fds[1]);
	wait(&status);
	wait(&status);
	sleep(1);
	ft_printf("I'm parent.\n");
}
