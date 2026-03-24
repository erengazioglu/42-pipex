/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:31:19 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/24 13:37:27 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;
	t_state	*state;

	state = init_state(argc, argv, envp);
	i = 1;
	while (i < argc - 2)
	{
		create_pipe(state);
		state->pid = fork();
		if (state->pid == -1)
			crash("fork creation");
		if (state->pid == 0)
			child_process(state, i);
		i++;
	}
	close_fds(state);
	i = 1;
	while (i++ < argc - 2)
	{
		wait(&(state->exit_code));
		if (state->exit_code)
			crash("child crashed");
	}
	ft_printf("I'm the parent.\n");
}
