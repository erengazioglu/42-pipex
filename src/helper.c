/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 02:25:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/24 13:35:23 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int crash(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

t_state	*init_state(int argc, char **argv, char **envp)
{
	t_state	*state;

	if (argc < 5)
	{
		errno = EINVAL;
		crash("Arg check");
	}
	state = ft_calloc(1, sizeof(t_state));
	state->fds[2] = open(argv[1], O_RDONLY);
	if (state->fds[2] == -1)
		crash("Open file (read)");
	state->fds[3] = open(
		argv[argc - 1], 
		O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
	);
	if (state->fds[3] == -1)
	{
		close(state->fds[2]);
		crash("Open file (write)");
	}
	state->argc = argc;
	state->argv = argv;
	state->envp = envp;
	return (state);
}

void	close_fds(t_state *state)
{
	close(state->fds[0]);
	close(state->fds[1]);
	close(state->fds[2]);
	close(state->fds[3]);
}

void	create_pipe(t_state *state)
{
	int	fd[2];

	if (pipe(fd) == -1)
		crash("pipe creation");
	state->fds[0] = fd[0];
	state->fds[1] = fd[1];
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
