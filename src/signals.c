/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 07:50:50 by ntan              #+#    #+#             */
/*   Updated: 2022/04/12 14:53:55 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_manager(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
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
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}
