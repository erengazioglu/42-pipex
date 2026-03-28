 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:32:30 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/28 01:08:29 by egaziogl         ###   ########.fr       */
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

# define FLAG_READ	0
# define FLAG_WRITE	1

typedef struct s_state {
	int		fd[3];
	int		exit_code;
	int		argc;
	char	**argv;
	char	**child_args;
	char	**envp;
	pid_t	pid;
}	t_state;

typedef enum e_err {
	ERR_NONE,
	ERR_ARGS,
	ERR_MALLOC,
	ERR_PIPE,
	ERR_FORK,
	ERR_OPENR,
	ERR_OPENW,
	ERR_DUP2,
	ERR_STR,
	ERR_EXEC,
	ERR_CMDNOTFOUND,
	ERR_CMDDENIED,
	ERR_CMDEMPTY
}	t_err;

// helper.c
void	close_fds(t_state *state, bool all);
void	custom_err(char *left, char *right);
char	*ft_pathjoin(char *s1, char *s2, bool free_s1);
void	free_strlist(char **list);

// child.c
void	child_process(t_state *state, int i);

// crash.c
int		crash(t_state *state, t_err err);

#endif
