/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/31 15:11:02 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	msh;

	(void)argc;
	(void)argv;
	init_prog(&msh, envp);

	struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = signal_manager;
	msh.sa = sa;
	
	while (1)
	{
		sigaction(SIGINT, &msh.sa, NULL);
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
