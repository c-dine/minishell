/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/28 11:46:06 by cdine            ###   ########.fr       */
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
		if (error_code > 0)
		{
			if (ft_process_line(readline("\e[1;31mminishell> \e[0m"), &minishell) == 1)
				break ;
		}
		else
		{
			if (ft_process_line(readline("\e[1;32mminishell> \e[0m"), &minishell) == 1)
				break ;
		}
	}
	rl_clear_history();
	memrelease();
	return (0);
}
