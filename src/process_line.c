/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:14:15 by cdine             #+#    #+#             */
/*   Updated: 2022/03/26 18:09:53 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_children(t_prog *msh)
{
	t_list	*temp;
	
	temp = msh->cmds->next;
	while (temp)
	{
		// printf("PID WAITED: %d\n", temp->content->pid);
		waitpid(temp->content->pid, NULL, 0);
		// printf("PID DONE: %d\n", temp->content->pid);
		temp = temp->next;
	}
	return (0);
}

int	fork_process(t_list *cmd, t_list *beginning)
{
	if (cmd->content->cmd_type == -1)
	{
		ft_error(CMD_NOT_FOUND, cmd->content->cmd[0]);
		return (1);
	}
	cmd->content->pid = fork();
	////////////////// PROTEGER FORK
	if (cmd->content->pid == 0)
	{
		if (open_fds(cmd->content) == -1)
		{
			close_all_pipes(beginning, -2,-2);
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
		close_all_pipes(beginning, -2, -2);
		close_trioput_fd(cmd);
		execve(cmd->content->cmd_path, cmd->content->cmd, 0);
		////////////// proteger execve
	}
	else
		close_main_process(cmd);
	// wait(NULL);
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
		printf("%s\n", getcwd(NULL, 0));
	else if (cmd->content->cmd_type == 6)
		ft_export(cmd->content->cmd, msh);
	else if (cmd->content->cmd_type == 7)
		ft_unset(cmd->content->cmd, msh);
	else if (cmd->content->cmd_type == 8)
		print_duotab(msh->envp);
	close_trioput_fd(cmd);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
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
	printf("\033[0;37m");
	if (ft_strlen(line) != 0)
		add_history(line);
	if (line)
		line = replace_var(line, minishell);
	else
		return (1);
	signal(SIGQUIT, SIG_DFL);/** Modifie le ctrl + \ pour interrompre programme en cours **/
	if (ft_parsing(line, minishell) == -1)
		return (-1);
    // check cmds with access ; if cmd_type == -2 -> pas de cmd, -1 -> not valid, 1 -> absolute path, 2 -> env cmd (comme ls), >= 3 -> builtin
	ft_check_cmds(minishell);
    // set pipes with fds && fork processes avec distinction entre builtins et cmds
	tmp = ft_processes(minishell);
	if (tmp == -1 || tmp == 1)
		return (tmp);
	wait_children(minishell);
	return (0);
}
