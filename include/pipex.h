/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:32:30 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/24 15:51:59 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define FLAG_READ	0x01
# define FLAG_WRITE	0x02

typedef struct s_state {
	int		fd[4];
	int		exit_code;
	int		argc;
	char	**argv;
	char	**child_args;
	char	**envp;
	pid_t	pid;
}	t_state;

// helper.c
int		crash(char *s);
void	close_fds(t_state *state);
t_state	*init_state(int argc, char **argv, char **envp);
void	pipe_and_fork(t_state *state);

// child.c
void	child_process(t_state *state, int i);

#endif
