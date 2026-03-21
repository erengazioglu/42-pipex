/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:32:30 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/21 03:25:02 by egaziogl         ###   ########.fr       */
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

# define FLAG_READ	0x01
# define FLAG_WRITE	0x02

int		crash(char *s);
void	check_args(int argc, char **argv, int *fds);
void	child_process(int argc, int *fds, int i);
void	close_all(int *fds);

#endif