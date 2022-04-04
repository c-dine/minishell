/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:14:15 by cdine             #+#    #+#             */
/*   Updated: 2022/04/04 12:48:23 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	wait_children(t_prog *msh)
{
	t_list	*temp;
	int		err;

	err = -1;
	temp = msh->cmds->next;
	while (temp)
	{
		waitpid(temp->content->pid, &err, 0);
		temp = temp->next;
	}
	if (err != -1 && error_code == 0)
		error_code = WEXITSTATUS(err);
	return (0);
}

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
		ft_cd(cmd->content->cmd);
	else if (cmd->content->cmd_type == 5)
		ft_pwd();
	else if (cmd->content->cmd_type == 6)
		ft_export(cmd->content->cmd, msh);
	else if (cmd->content->cmd_type == 7)
		ft_unset(cmd->content->cmd, msh);
	else if (cmd->content->cmd_type == 8)
		print_duotab(msh->envp);
	close_trioput_fd(cmd);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close_main_process(cmd, 1);
	error_code = 0;
	return (0);
}

void	no_cmd(t_list *cmd)
{
	open_fds(cmd->content);
	close_trioput_fd(cmd);
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
			fork_process(temp, beginning);
		else if (temp->content->cmd_type == -2)
			no_cmd(temp);
		else
			ft_builtin(temp, msh);
		temp = temp->next;
	}
	// close_all_pipes(beginning, -2, -2);
	return (0);
}

int	ft_check_specialchar(char *line)
{
	int	i;
	int	tmp;

	tmp = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == ':')
		{
			tmp++;
			error_code = 0;
		}
		if (line[i] == '!')
		{
			tmp++;
			error_code = 1;
		}
		if (line[i])
			i++;
	}
	if (tmp == 1 && line[i] == '\0')
		return (1);
	error_code = 0;
	return (0);
}

int	ft_process_line(char *line, t_prog *minishell)
{
	int	tmp;

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
		return (-1);  // -1 pour que ca relance la boucle du main
    // check cmds with access ; if cmd_type == -2 -> pas de cmd, -1 -> not valid, 1 -> absolute path, 2 -> env cmd (comme ls), >= 3 -> builtin
	ft_check_cmds(minishell);
    // set pipes with fds && fork processes avec distinction entre builtins et cmds
	tmp = ft_processes(minishell);
	if (tmp == -1 || tmp == 1)
		return (tmp);
	wait_children(minishell);
	return (0);
}
