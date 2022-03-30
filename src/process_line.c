/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:14:15 by cdine             #+#    #+#             */
/*   Updated: 2022/03/30 15:25:21 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (err != -1)
		error_code = WEXITSTATUS(err);
	return (0);
}

int	fork_process(t_list *cmd, t_list *beginning)
{
	if (cmd->content->cmd_type == -1 && (!cmd->content->cmd_path || access(cmd->content->cmd_path, F_OK) == -1))
	{
		if (cmd->content->cmd_path == NULL)
			return (ft_error(CMD_NOT_FOUND, cmd->content->cmd[0], 127), 1);
		else
			return (ft_error(FILE_NOT_FOUND, cmd->content->cmd_path, 127), 1);
	}
	cmd->content->pid = fork();
	if (cmd->content->pid == -1)
		return (ft_error(FORK_ERROR, "fork", 1), 1);
	if (cmd->content->pid == 0)
	{
		/**SIGNAL DU CHILD**/
		signal(SIGINT, SIG_DFL);
		if (open_fds(cmd->content) == -1)
		{
			close_all_pipes(beginning);
			exit(1);
		}
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
		if (execve(cmd->content->cmd_path, cmd->content->cmd, 0) == -1)
			return (ft_error(PERMISSION_DENIED, cmd->content->cmd_path, 126), 1);
	}
	else
		close_main_process(cmd, 0);
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

int	ft_process_line(char *line, t_prog *minishell)
{
	int	tmp;
	
	if (line && ft_strlen(line) != 0)
		add_history(line);
	if (line)
		line = replace_var(line, minishell);
	else
		return (1);
	signal(SIGQUIT, SIG_DFL);
	// printf("%s\n", line);
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
