/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:04:05 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/24 15:24:09 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/stat.h>

/*

Launch this with 3 arguments:
./execve files/infile command files/outfile

*/

int crash(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
void	check_args(int argc, char **argv, int *fds)
{
	if (argc != 4)
	{
		errno = EINVAL;
		crash("Arg check");
	}
	fds[0] = open(argv[1], O_RDONLY);
	if (fds[0] == -1)
		crash("Open file (read)");
	fds[1] = open(
		argv[3], 
		O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
	);
	if (fds[1] == -1)
	{
		close(fds[0]);
		crash("Open file (write)");
	}
}

void	redirect(int argc, int *fds, int i)
{
	(void) i;
	(void) argc;
	close(0);
	close(1);
	dup2(fds[0], 0);
	dup2(fds[1], 1);
}

char	*ft_pathjoin(char *s1, char *s2, bool free_s1)
{
	char	*result;
	char	*result_base;
	char	*s1_base;

	if (ft_strchr(s2, '/'))
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!result)
	{
		if (free_s1)
			free(s1);
		return (NULL);
	}
	result_base = result;
	s1_base = s1;
	while (*s1)
		*(result++) = *(s1++);
	*(result++) = '/';
	while (*s2)
		*(result++) = *(s2++);
	*result = '\0';
	if (free_s1)
		free(s1_base);
	return (result_base);
}

char	**extract_paths(char **envp, char *fn)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{

		if (ft_str_startswith(envp[i], "PATH="))
		{
			paths = ft_split(envp[i] + 5, ':');
			break;
		}
		i++;
	}
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_pathjoin(paths[i], fn, true);
		i++;
	}
	return (paths);
}




int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	char	**command;
	char	**paths;

	check_args(argc, argv, fd);
	pid = fork();
	if (pid == -1)
		crash("forking");
	if (pid == 0)
	{
		command = ft_split(argv[2], ' ');
		redirect(argc, fd, 0);
		if (ft_strchr(command[0], '/'))
			execve(*command, command, envp);
		else
		{
			paths = extract_paths(envp, command[0]);
			for (int i = 0; paths[i]; i++)
			{
				command[0] = paths[i];
				execve(paths[i], command, envp);
			}
		}
		crash("exec");
	}
	close(fd[0]);
	close(fd[1]);
}
