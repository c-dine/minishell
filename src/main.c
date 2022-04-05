/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/04/05 19:23:16 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	msh;
	int		save_in;

	(void)argc;
	(void)argv;
	init_prog(&msh, envp);
	rl_outstream = stderr;
	while (1)
	{
		save_in = dup(STDIN_FILENO);
		signal(SIGINT, signal_manager);
		signal(SIGQUIT, SIG_IGN);
		g_error_code = 0;
		if (ft_process_line(readline("minishell> "), &msh) == 1)
			break ;
		if (g_error_code == 130)
			dup2(save_in, STDIN_FILENO);
		msh.prev_err_code = g_error_code;
		close(save_in);
	}
	// printf("BYE MINISHELL\n");
	rl_clear_history();
	memrelease();
	return (g_error_code);
}
