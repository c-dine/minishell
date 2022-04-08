/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/04/08 17:41:04 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	msh;

	(void)argc;
	(void)argv;
	init_prog(&msh, envp);
	rl_outstream = stderr;
	while (1)
	{
		msh.fd_to_close_1 = dup(STDIN_FILENO);
		signal(SIGINT, signal_manager);
		signal(SIGQUIT, SIG_IGN);
		g_error_code = 0;
		if (ft_process_line(readline("minishell> "), &msh) == 1)
			break ;
		if (g_error_code == 130)
			dup2(msh.fd_to_close_1, STDIN_FILENO);
		msh.prev_err_code = g_error_code;
		close(msh.fd_to_close_1);
	}
	// printf("BYE MINISHELL\n");
	rl_clear_history();
	memrelease();
	close_fds_to_close(&msh);
	return (g_error_code);
}
