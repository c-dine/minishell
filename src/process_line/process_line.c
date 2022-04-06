/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:14:15 by cdine             #+#    #+#             */
/*   Updated: 2022/04/06 15:53:47 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_processes(t_prog *msh)
{
	t_list	*temp;
	t_list	*beginning;

	temp = msh->cmds->next;
	beginning = temp;
	while (temp)
	{
		if (!temp->content->cmd)
		{
			temp = temp->next;
			continue ;
		}
		if (temp->content->cmd_type < 3 && temp->content->cmd_type != -2)
			fork_process(temp, beginning, msh);
		else if (temp->content->cmd_type == -2)
			no_cmd(temp);
		else
			ft_fork_builtins(temp, msh);
		temp = temp->next;
	}
	return (0);
}

int	ft_process_line(char *rdline, t_prog *minishell)
{
	int		tmp;
	char	*line;

	if (!rdline)
		return (1);
	line = ft_strdup(rdline);
	free(rdline);
	if (line && ft_strlen(line) != 0)
		add_history(line);
	if (!line)
		return (1);
	if (line == NULL)
		return (ft_error(QUOTE_NOT_CLOSED, "minishell", 1), -1);
	if (ft_check_specialchar(line) == 1)
		return (0);
	if (ft_parsing(line, minishell) == -1)
		return (-1);
	ft_check_cmds(minishell);
	tmp = ft_processes(minishell);
	if (tmp == -1 || tmp == 1)
		return (tmp);
	wait_children(minishell);
	return (0);
}
