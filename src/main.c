/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/22 14:37:49 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	minishell;

	(void)argc;
	(void)argv;
	printf("\e[1;1H\e[2J");
	init_prog(&minishell, envp);
	signal(SIGINT, signal_manager);
	while (1)
	{
		printf("\033[1;33m");
		signal(SIGQUIT, SIG_IGN);
		if (ft_process_line(readline("minishell> "), &minishell) == 1)
			return (0);
		close_fds(&minishell);
	}
	memrelease();
	return (0);
}
