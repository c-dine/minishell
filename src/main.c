/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/04/05 16:42:17 by ntan             ###   ########.fr       */
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
	rl_outstream = stderr;
	// int fd;
	// fd = open("test", O_RDWR);
	// dup2(fd, STDERR_FILENO);
	while (1)
	{
		save_in = dup(STDIN_FILENO);
		sigaction(SIGINT, &msh.sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		// printf("\n%d\n", g_error_code);
		if (ft_process_line(readline("minishell> "), &msh) == 1)
			break ;
		if (g_error_code == 130)
		{
			dup2(save_in, STDIN_FILENO);
			// // rl_replace_line("", 0);
		}
		close(save_in);
	}
	// printf("BYE MINISHELL\n");
	rl_clear_history();
	memrelease();
	return (g_error_code);
}
