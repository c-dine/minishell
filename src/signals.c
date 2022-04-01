/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 07:50:50 by ntan              #+#    #+#             */
/*   Updated: 2022/04/01 13:09:01 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_manager(int sig, siginfo_t *si, void *unused)
{
	(void)unused;
	(void)si;
	
	if (sig == SIGINT)
	{
		if (si->si_pid == getpid())
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			printf("\n");
		error_code = 130;
	}
	else if (sig == SIGQUIT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		
	}
}

void	signal_heredoc(int sig)
{
	// int save_in;
	
	if (sig == SIGINT)
	{
		error_code = 130;
		// save_in = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		// dup2(save_in, STDIN_FILENO);
	}
}