/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:14:15 by cdine             #+#    #+#             */
/*   Updated: 2022/04/05 14:34:35 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_builtin(t_list *cmd, t_prog *msh)
{
	int	fd_out;

	fd_out = dup(STDOUT_FILENO);
	if (open_fds(cmd->content) == -1)
		return (-1);
	if (cmd->content->output_fd != -2)
		dup2(cmd->content->output_fd, STDOUT_FILENO);
	else if (cmd->next)
		dup2(cmd->next->content->pipe[1], STDOUT_FILENO);
	if (cmd->content->cmd_type == 3)
		ft_echo(cmd->content->cmd);
	else if (cmd->content->cmd_type == 4)
		ft_cd(cmd->content->cmd, msh);
	else if (cmd->content->cmd_type == 5)
		ft_pwd();
	else if (cmd->content->cmd_type == 6)
		ft_export(cmd->content->cmd, msh);
	else if (cmd->content->cmd_type == 7)
		ft_unset(cmd->content->cmd, msh);
	else if (cmd->content->cmd_type == 8)
		print_duotab(msh->envp);
	dup2(fd_out, STDOUT_FILENO);
	ft_close_builtin(fd_out, cmd);
	return (0);
}

int	ft_processes(t_prog *msh)
{
	t_list	*temp;
	t_list	*beginning;

	temp = msh->cmds->next;
	beginning = temp;
	while (temp)
	{
		if (temp->content->cmd_type == 9)
			return (1);
		if (temp->content->cmd_type < 3 && temp->content->cmd_type != -2)
			fork_process(temp, beginning, msh);
		else if (temp->content->cmd_type == -2)
			no_cmd(temp);
		else
			ft_builtin(temp, msh);
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
	if (line)
		line = replace_var(line, minishell);
	else
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
