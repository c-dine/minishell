/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 07:50:50 by ntan              #+#    #+#             */
/*   Updated: 2022/03/28 19:27:02 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_manager(int sig)
{
	if (sig == SIGINT)
	{
		error_code = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		close(STDIN_FILENO);
	}
	// else if (sig == SIGQUIT)
	// {
	// 	error_code = 131;
	// 	printf("^'\'Quit (core dumped)\n");
	// 	exit(0);
	// }
}

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		error_code = 130;
		printf("\n");
	}
}