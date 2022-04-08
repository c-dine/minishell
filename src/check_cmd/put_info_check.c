/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:00:08 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 13:08:05 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_doesnt_work(t_list *temp)
{
	temp->content->cmd_type = -2;
	if (temp->content->cmd[0] && (temp->content->cmd[0][0] == '\0'
		|| ft_strncmp(temp->content->cmd[0], "..", 2) == 0
		|| ft_strncmp(temp->content->cmd[0], ".", 2) == 0))
		temp->content->cmd_type = -1;
	temp = temp->next;
}

void	cmd_works(t_list *temp, t_prog *msh)
{
	int	tmp;

	temp->content->cmd_type = check_is_builtin(temp->content->cmd[0]);
	if (temp->content->cmd_type == -1)
	{
		if (ft_findslash(temp->content->cmd[0]) == 1)
		{
			temp->content->cmd_type = check_path(temp->content->cmd[0], 1);
			temp->content->cmd_path = ft_strdup(temp->content->cmd[0]);
			ft_get_cmdname(temp->content->cmd);
		}
		else
		{
			tmp = check_path(get_absolute_path(temp->content->cmd[0],
						msh->envp), 2);
			temp->content->cmd_type = tmp;
			temp->content->cmd_path = get_absolute_path(temp->content->cmd[0],
					msh->envp);
		}
	}
}

void	ft_check_cmds(t_prog *msh)
{
	t_list	*temp;

	temp = msh->cmds->next;
	while (temp)
	{
		if (!temp->content->cmd)
		{
			temp = temp->next;
			continue ;
		}
		if (temp->content->cmd[0] == NULL || temp->content->cmd[0][0] == '\0'
			|| ft_strncmp(temp->content->cmd[0], "..", 2) == 0
			|| ft_strncmp(temp->content->cmd[0], ".", 2) == 0)
			cmd_doesnt_work(temp);
		else
			cmd_works(temp, msh);
		temp = temp->next;
	}
}
