/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:32:30 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/23 16:14:23 by egaziogl         ###   ########.fr       */
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
	int		fds[4];
	int		exit_code;
	int		argc;
	char	**argv;
	char	**envp;
	pid_t	pid;
}	t_state;

int		crash(char *s);
// void	check_args(int argc, char **argv, int *fds);
void	child_process(t_state *state, int i);
void	close_fds(t_state *state);
t_state	*init_state(int argc, char **argv, char **envp);

#endif
