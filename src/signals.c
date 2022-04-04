/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 07:50:50 by ntan              #+#    #+#             */
/*   Updated: 2022/04/04 18:56:21 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_manager(int sig, siginfo_t *si, void *unused)
{
	(void)unused;
	(void)si;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_error_code = 130;
	}
}

// void	signal_bs(int sig)
// {
// 	(void)sig;
// 	g_error_code = 131;
// 	printf(" \n");
// 	signal(SIGQUIT, SIG_DFL);
// }

void	signal_fork(int sig)
{
	if (sig == SIGINT)
	{
		g_error_code = 130;
		// printf("\n");
		close(STDIN_FILENO);
		// printf("\n");
	}
}

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_error_code = 130;
		printf("\n");
		close(STDIN_FILENO);
	}
}
