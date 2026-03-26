/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:28:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/26 15:20:35 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	handle_init_crash(t_state *state, t_err err)
{
	if (err == ERR_ARGS)
		errno = EINVAL;
	if (err == ERR_MALLOC)
		errno = ENOMEM;
	(void) state;
	perror("init");
}
static void	handle_spawn_crash(t_state *state, t_err err)
{
	if (err == ERR_PIPE)
		// nothing happens
	if (err > ERR_PIPE)
	{
		close_fds(state);
	}
		// close pipe and crash!
	(void) err;
	(void) state;
	perror("spawn");
}

static void	handle_child_crash(t_state *state, t_err err)
{
	(void) err;
	(void) state;
	perror("child");
}

int crash(t_state *state, t_err err)
{
	int	lasterr = errno;
	if (err <= ERR_OPENW)
		handle_init_crash(state, err);
	else if (err <= ERR_DUP2)
		handle_spawn_crash(state, err);
	else if (err <= ERR_EXEC)
		handle_child_crash(state, err);
	free(state);
	if (lasterr == EACCES || lasterr == EISDIR || lasterr == ENOEXEC)
		exit(126);
	if (lasterr == ENOENT)
		exit(127);
	exit(1);
}

// int
