/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/27 20:00:45 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	minishell;

	(void)argc;
	(void)argv;
	init_prog(&minishell, envp);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		if (ft_process_line(readline("\e[1;34mminishell> \e[0m"), &minishell) == 1)
			break ;
	}
	rl_clear_history();
	memrelease();
	return (0);
}
