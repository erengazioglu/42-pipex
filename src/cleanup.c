/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:28:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/26 18:22:02 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static t_err	handle_init_crash(t_state *state, t_err err)
{
	if (err == ERR_ARGS)
		errno = EINVAL;
	if (err == ERR_MALLOC)
		errno = ENOMEM;
	if (err == ERR_OPENR)
		close_fds(state);
	if (err == ERR_OPENW)
		close(state->fd[1]);
		
	(void) state;
	perror("init");
	return (err);
}
static t_err	handle_spawn_crash(t_state *state, t_err err)
{
	if (err > ERR_PIPE)
		close_fds(state);
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
		perror(NULL);
	}
	else
		perror(NULL);
	close_fds(state);
	return (err);
}

int crash(t_state *state, t_err err)
{
	int		lasterr;
	t_err	custom_err;
	
	lasterr = errno;
	if (err <= ERR_OPENW)
		custom_err = handle_init_crash(state, err);
	else if (err <= ERR_DUP2)
		custom_err = handle_spawn_crash(state, err);
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

// int
