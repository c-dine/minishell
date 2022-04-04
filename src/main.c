/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/04/04 15:33:44 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	msh;
	(void)argc;
	(void)argv;

	init_prog(&msh, envp, &msh.sa);
	while (1)
	{
		sigaction(SIGINT, &msh.sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		printf("\n%d\n", error_code);
		if (ft_process_line(readline("minishell> "), &msh) == 1)
			break ;
		// if (error_code > 0)
		// {
		// 	if (ft_process_line(readline("\e[1;31mminishell> \e[0m"), &msh) == 1)
		// 		break ;
		// }
		// else
		// {
		// 	if (ft_process_line(readline("\e[1;32mminishell> \e[0m"), &msh) == 1)
		// 		break ;
		// }
	}
	printf("BYE MINISHELL\n");
	rl_clear_history();
	memrelease();
	return (0);
}
