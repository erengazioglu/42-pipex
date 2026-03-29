/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:28:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/29 15:11:19 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static t_err	handle_init_crash(t_err err)
{
	if (err == ERR_ARGS)
		errno = EINVAL;
	if (err == ERR_MALLOC)
		errno = ENOMEM;
	custom_err("init", strerror(errno));
	return (err);
}

static t_err	handle_open_crash(t_state *state, t_err err)
{
	char	*error;
	char	*file;

	error = strerror(errno);
	if (err == ERR_OPENR)
		file = state->argv[1];
	if (err == ERR_OPENW)
		file = state->argv[state->argc - 1];
	custom_err(file, error);
	close_fds(state, true);
	free_strlist(state->child_args);
	return (err);
}

static t_err	handle_spawn_crash(t_state *state, t_err err)
{
	if (err > ERR_PIPE)
		close_fds(state, false);
	free_strlist(state->child_args);
	perror("spawn");
	return (ERR_NONE);
}

static t_err	handle_child_crash(t_state *state, t_err err)
{
	if (err == ERR_CMDNOTFOUND)
		custom_err(state->child_args[0], "command not found");
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

int	crash(t_state *state, t_err err)
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
	if (custom_err == ERR_CMDEMPTY || lasterr == EACCES
		|| lasterr == EISDIR || lasterr == ENOEXEC)
		exit(126);
	if (lasterr == ENOENT)
		exit(127);
	exit(1);
}
