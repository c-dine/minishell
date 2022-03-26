/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/26 18:17:26 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	minishell;

	(void)argc;
	(void)argv;
	// printf("\e[1;1H\e[2J");
	init_prog(&minishell, envp);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		printf("\033[1;33m");
		signal(SIGQUIT, SIG_IGN);
		if (ft_process_line(readline("minishell> "), &minishell) == 1)
			break ;
	}
	rl_clear_history();
	memrelease();
	return (0);
}
