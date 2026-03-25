/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:28:22 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/25 17:35:12 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	open_file(t_state *state, int flag)
{
	int	fd;
	int	fd_keep;

	if (flag == FLAG_READ)
	{
		fd = open(state->argv[1], O_RDONLY);
		if (fd == -1)
			crash(state, ERR_OPENR);
	}
	else if (flag == FLAG_WRITE)
	{
		fd = open(state->argv[state->argc - 1], 
			O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
		);
		if (fd == -1)
			crash(state, ERR_OPENW);
	}
	fd_keep = dup2(fd, flag);
	if (fd_keep == -1)
		crash(state, ERR_DUP2);
	close(fd);
}

static void	redirect(t_state *state, int n)
{
	int	fd;

	if (n == 1)
		open_file(state, FLAG_READ);
	else
		fd = dup2(state->fd[0], 0);
	if (n == state->argc - 3)
		open_file(state, FLAG_WRITE);
	else
		dup2(state->fd[1], 1);
	if (fd == -1)
		crash(state, ERR_DUP2);
	close_fds(state);
}

static char	**extract_paths(t_state *state)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = 0;
	while (state->envp[i])
	{
		if (ft_str_startswith(state->envp[i], "PATH="))
		{
			paths = ft_split(state->envp[i] + 5, ':');
			break;
		}
		i++;
		if (!state->envp[i])
			crash(state, ERR_PATH);
	}
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_pathjoin(paths[i], state->child_args[0], true);
		if (!paths[i])
			crash(state, ERR_STR);
		i++;
	}
	return (paths);
}

void	child_process(t_state *state, int n)
{
	char	**paths;
	char	**args;
	
	args = ft_split(state->argv[n + 1], ' ');
	if (!args)
		crash(state, ERR_STR);
	redirect(state, n);
	if (ft_strchr(*args, '/'))
		execve(*args, args, state->envp);
	state->child_args = args;
	paths = extract_paths(state);
	for (int i = 0; paths[i]; i++)
	{
		args[0] = paths[i];
		execve(*args, args, state->envp);
	}
	crash(state, ERR_EXEC);
}
