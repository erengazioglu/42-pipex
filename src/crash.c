/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:28:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/28 13:02:11 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static t_err	handle_init_crash(t_err err)
{
	if (err == ERR_ARGS)
		errno = EINVAL;
	if (err == ERR_MALLOC)
		errno = ENOMEM;
	perror("init");
	return (err);
}

static t_err	handle_open_crash(t_state *state, t_err err)
{
	char *error = strerror(errno);
	char	*file;
	
	if (err == ERR_OPENR)
		file = state->argv[1];
		// close_fds(state, true);
	if (err == ERR_OPENW)
		file = state->argv[state->argc - 1];
		// close(state->fd[2]);
	close_fds(state, true);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	free_strlist(state->child_args);
	return (err);
}
static t_err	handle_spawn_crash(t_state *state, t_err err)
{
	if (err > ERR_PIPE)
		close_fds(state, false);
	(void) err;
	free_strlist(state->child_args);
	perror("spawn");
	return (ERR_NONE);
}

static t_err	handle_child_crash(t_state *state, t_err err)
{
	if (err == ERR_CMDNOTFOUND)
		write(2, "command not found\n", 18);
	else if (err == ERR_CMDDENIED)
	{
		errno = EACCES;
		perror("child denied");
	}
	else
		perror("child");
	free_strlist(state->child_args);
	close_fds(state, false);
	return (err);
}

int crash(t_state *state, t_err err)
{
	int		lasterr;
	t_err	custom_err;
	
	lasterr = errno;
	if (err <= ERR_MALLOC)
		custom_err = handle_init_crash(err);
	else if (err <= ERR_FORK)
		custom_err = handle_spawn_crash(state, err);
	else if (err <= ERR_OPENW)
		custom_err = handle_open_crash(state, err);
	else
		custom_err = handle_child_crash(state, err);
	free(state);
	if (custom_err == ERR_OPENW)
		exit(1);
	if (custom_err == ERR_CMDNOTFOUND)
		exit(127);
	if (custom_err == ERR_CMDEMPTY || 
		lasterr == EACCES || lasterr == EISDIR || lasterr == ENOEXEC)
		exit(126);
	if (lasterr == ENOENT)
		exit(127);
	exit(1);
}

