/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:47:46 by cdine             #+#    #+#             */
/*   Updated: 2022/04/07 17:40:03 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dup_pipes(t_list *cmd, t_list *beginning)
{
	if (cmd->content->input_fd != -2)
		dup2(cmd->content->input_fd, STDIN_FILENO);
	else if (cmd->content->pipe[0] != -2)
		dup2(cmd->content->pipe[0], STDIN_FILENO);
	if (cmd->content->output_fd != -2)
		dup2(cmd->content->output_fd, STDOUT_FILENO);
	else if (cmd->next)
		dup2(cmd->next->content->pipe[1], STDOUT_FILENO);
	close_all_pipes(beginning);
	close_trioput_fd(cmd);
}

int	cmd_pb(t_list *cmd, t_list *beginning)
{
	if (ft_strncmp(cmd->content->cmd[0], ".", 2) == 0)
		ft_error(FILENAME_REQUIRED, ".", 2);
	else if (cmd->content->cmd_path == NULL || (cmd->content->cmd
			&& (cmd->content->cmd[0][0] == '\0'
			|| ft_strncmp(cmd->content->cmd[0], "..", 2) == 0)))
		ft_error(CMD_NOT_FOUND, cmd->content->cmd[0], 127);
	else if (access(cmd->content->cmd_path, F_OK) != -1
		&& access(cmd->content->cmd_path, X_OK) == -1)
		ft_error(FILE_NOT_FOUND, cmd->content->cmd_path, 127);
	close_all_pipes(beginning);
	if (ft_strncmp(cmd->content->cmd[0], ".", 2) == 0)
		return (2);
	return (127);
}

int	permission_denied(t_list *cmd, t_list *beginning)
{
	ft_error(PERMISSION_DENIED, cmd->content->cmd_path, 126);
	close_all_pipes(beginning);
	return (126);
}

int	fork_process(t_list *cmd, t_list *beginning, t_prog *msh)
{
	signal(SIGINT, signal_fork);
	cmd->content->pid = fork();
	if (cmd->content->pid == -1)
		return (ft_error(FORK_ERROR, "fork", 1), 1);
	if (cmd->content->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (open_fds(cmd->content) == -1)
			exit(1);
		if ((cmd->content->cmd_type == -1
				&& (!cmd->content->cmd_path || access(cmd->content->cmd_path,
						F_OK) == -1)))
			exit(cmd_pb(cmd, beginning));
		if (cmd->content->cmd_type == 1 && access(cmd->content->cmd_path,
				X_OK) == -1)
			exit(permission_denied(cmd, beginning));
		dup_pipes(cmd, beginning);
		if (execve(cmd->content->cmd_path, cmd->content->cmd, msh->envp) == -1)
			return (ft_error(PERMISSION_DENIED, cmd->content->cmd_path,
					126), 1);
	}
	else
		close_main_process(cmd, 0);
	return (0);
}
