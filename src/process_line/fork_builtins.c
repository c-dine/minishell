/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:21:43 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 12:29:35 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dup_stdout(t_list *cmd)
{
	if (cmd->content->output_fd != -2)
		dup2(cmd->content->output_fd, STDOUT_FILENO);
	else if (cmd->next)
		dup2(cmd->next->content->pipe[1], STDOUT_FILENO);
}

int	ft_builtin(t_list *cmd, t_prog *msh)
{
	int	fd_out;
	int	ret;

	ret = 0;
	fd_out = dup(STDOUT_FILENO);
	if (open_fds(cmd->content) == -1)
		return (-1);
	dup_stdout(cmd);
	if (cmd->content->cmd_type == 3)
		ret = ft_echo(cmd->content->cmd);
	else if (cmd->content->cmd_type == 4)
		ret = ft_cd(cmd->content->cmd, msh);
	else if (cmd->content->cmd_type == 5 && ft_pwd() != NULL)
		ret = ft_pwd_builtin();
	else if (cmd->content->cmd_type == 6)
		ret = ft_export(cmd->content->cmd, msh);
	else if (cmd->content->cmd_type == 7)
		ret = ft_unset(cmd->content->cmd, msh);
	else if (cmd->content->cmd_type == 8)
		ft_env(msh);
	else if (cmd->content->cmd_type == 9)
		ret = ft_exit(cmd->content->cmd, msh);
	return (dup2(fd_out, STDOUT_FILENO), ft_close_builtin(fd_out, cmd), ret);
}

int	ft_count_cmds(t_prog *msh)
{
	t_list	*temp;
	int		count;

	count = 0;
	temp = msh->cmds->next;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	ft_fork_builtins(t_list *cmd, t_prog *msh)
{
	if (ft_count_cmds(msh) > 1)
	{
		signal(SIGINT, signal_fork);
		cmd->content->pid = fork();
		if (cmd->content->pid == -1)
			return (ft_error(FORK_ERROR, "fork", 1), 1);
		if (cmd->content->pid == 0)
		{
			ft_shlvl(msh, 0);
			signal(SIGQUIT, SIG_DFL);
			exit(ft_builtin(cmd, msh));
		}
		else
			close_main_process(cmd, 0);
	}
	else
		ft_builtin(cmd, msh);
	return (0);
}
