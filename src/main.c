/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/04/04 18:51:53 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	msh;
	int		save_in;
	(void)argc;
	(void)argv;
	init_prog(&msh, envp, &msh.sa);
	while (1)
	{
		save_in = dup(STDIN_FILENO);
		sigaction(SIGINT, &msh.sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		// printf("\n%d\n", g_error_code);
		if (ft_process_line(readline("minishell> "), &msh) == 1)
				break ;
		if (g_error_code == 130)
			dup2(save_in, STDIN_FILENO);
		close(save_in);
	}
	printf("BYE MINISHELL\n");
	rl_clear_history();
	memrelease();
	return (0);
}
