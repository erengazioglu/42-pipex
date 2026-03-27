/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:28:22 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/27 11:31:10 by egaziogl         ###   ########.fr       */
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
	else
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

static void	check_paths(t_state *state, char **paths)
{
	int	result;

	result = -1;
	for (int i = 0; paths[i] && result; i++)
		result &= access(paths[i], F_OK);
	if (result == -1)
	{
		free_strlist(paths);
		crash(state, ERR_CMDNOTFOUND);
	}
	result = -1;
	for (int i = 0; paths[i] && result; i++)
		result &= access(paths[i], X_OK);
	if (result == -1)
	{
		free_strlist(paths);
		crash(state, ERR_CMDDENIED);
	}
}

static void	redirect(t_state *state, int n)
{
	int	fd;

	fd = 0;
	if (n == 1)
		open_file(state, FLAG_READ);
	else
		fd = dup2(state->fd[0], 0);
	close(state->fd[0]);
	if (n == state->argc - 3)
		open_file(state, FLAG_WRITE);
	else
		fd = dup2(state->fd[1], 1);
	close(state->fd[1]);
	if (fd == -1)
		crash(state, ERR_DUP2);
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
			crash(state, ERR_CMDNOTFOUND);
	}
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_pathjoin(paths[i], state->child_args[0], true);
		if (!paths[i])
			crash(state, ERR_MALLOC);
		i++;
	}
	return (paths);
}

void	child_process(t_state *state, int n)
{
	char	**paths;
	
	state->child_args = ft_split(state->argv[n + 1], ' ');
	if (!state->child_args)
		crash(state, ERR_STR);
	if (!(*(state->child_args)))
		crash(state, ERR_CMDNOTFOUND);
	redirect(state, n);
	if (ft_strchr(*state->child_args, '/'))
	{
		execve(state->child_args[0], state->child_args, state->envp);
		crash(state, ERR_EXEC);
	}
	if (!*(state->envp))
		crash(state, ERR_CMDNOTFOUND);
	paths = extract_paths(state);
	check_paths(state, paths);
	for (int i = 0; paths[i]; i++)
	{
		state->child_args[0] = paths[i];
		execve(state->child_args[0], state->child_args, state->envp);
	}
	free_strlist(paths);
	crash(state, ERR_EXEC);
}
