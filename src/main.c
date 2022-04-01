/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/04/01 16:38:28 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	msh;
	struct sigaction sa;
	(void)argc;
	(void)argv;
	
	init_prog(&msh, envp, &sa);
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		if (error_code > 0)
		{
			if (ft_process_line(readline("\e[1;31mminishell> \e[0m"), &msh) == 1)
				break ;
		}
		else
		{
			if (ft_process_line(readline("\e[1;32mminishell> \e[0m"), &msh) == 1)
				break ;
		}
	}
	printf("BYE MINISHELL\n");
	rl_clear_history();
	memrelease();
	return (0);
}
