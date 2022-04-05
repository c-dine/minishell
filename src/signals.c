/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 07:50:50 by ntan              #+#    #+#             */
/*   Updated: 2022/04/05 14:35:23 by ntan             ###   ########.fr       */
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

void	signal_fork(int sig)
{
	if (sig == SIGINT)
	{
		g_error_code = 130;
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_error_code = 130;
		printf("\n");
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}
