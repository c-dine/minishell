/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:35:12 by ntan              #+#    #+#             */
/*   Updated: 2022/04/08 13:32:44 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_pipes(t_list *beg_all_pipes)
{
	t_list	*temp;

	temp = beg_all_pipes;
	while (temp)
	{
		if (temp->content->pipe[0] != -2)
			close(temp->content->pipe[0]);
		if (temp->content->pipe[1] != -2)
			close(temp->content->pipe[1]);
		temp = temp->next;
	}
}

void	close_main_process(t_list *node, int builtin)
{
	if (node->content->cmd_i != 0 && builtin == 0)
		close(node->content->pipe[0]);
	if (node->next)
		close(node->next->content->pipe[1]);
}

void	close_trioput_fd(t_list *cmd)
{
	if (cmd->content->input_fd > 0)
		close(cmd->content->input_fd);
	if (cmd->content->output_fd > 0)
		close(cmd->content->output_fd);
	if (cmd->content->input_type == 2)
		unlink(cmd->content->heredoc->temp);
}
