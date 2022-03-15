/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/15 17:23:24 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	minishell;

	(void)argc;
	(void)argv;
	init_prog(&minishell, envp);
	// signal_manager(&minishell);
	while (1)
	{
		printf("\033[1;33m");
		ft_process_line(readline("minishell> "), &minishell);
		// if (ft_strcmp(minishell.cmds->content.cmd[0], "exit") == 0)
		// 	break ;
	}
	memrelease();
	return (0);
}
