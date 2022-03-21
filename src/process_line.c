/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:14:15 by cdine             #+#    #+#             */
/*   Updated: 2022/03/21 13:14:08 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_fd(int *fd_tab)
{
	int	i;
	int	ret;

	ret = -2;
	i = 0;
	while (fd_tab[i] != -2)
	{
		ret = fd_tab[i];
		i++;
	}
	return (ret);
}

int	fork_process(t_list *cmd, char **envp)
{
	if (get_fd(cmd->content->input_fd) == -1)
	{
		close_pipe(cmd->content->pipe);
		ft_error(FILE_NOT_FOUND);
		return (1);
	}
	if (cmd->content->cmd_type == -1)
	{
		close_pipe(cmd->content->pipe);
		ft_error(CMD_NOT_FOUND);
		return (1);
	}
	cmd->content->pid = fork();
	////////////////// PROTEGER FORK
	if (cmd->content->pid == 0)
	{
		if (get_fd(cmd->content->input_fd) != -2)
			dup2(get_fd(cmd->content->input_fd), STDIN_FILENO);
		else
			dup2(cmd->content->pipe[0], STDIN_FILENO);
		if (get_fd(cmd->content->output_fd) != -2)
			dup2(get_fd(cmd->content->output_fd), STDOUT_FILENO);
		else if (cmd->next)
			dup2(cmd->next->content->pipe[1], STDOUT_FILENO);
		close_pipe(cmd->content->pipe);
		execve(get_absolute_path(cmd->content->cmd[0], envp), cmd->content->cmd, 0);
		////////////// proteger execve
	}
	close_pipe(cmd->content->pipe);
	return (0);
}

int	ft_builtin(t_list *cmd)
{
	if (get_fd(cmd->content->output_fd) != -2)
		dup2(get_fd(cmd->content->output_fd), STDOUT_FILENO);
	else if (cmd->next)
		dup2(cmd->next->content->pipe[1], STDOUT_FILENO);
	if (cmd->content->cmd_type == 3)
		ft_echo(cmd->content->cmd);
	// else if (cmd->content->cmd_type == 4)
	// 	ft_cd(cmd->content->cmd);
	// else if (cmd->content->cmd_type == 5)
	// 	ft_pwd(cmd->content->cmd);
	// else if (cmd->content->cmd_type == 6)
	// 	ft_export(cmd->content->cmd);
	// else if (cmd->content->cmd_type == 7)
	// 	ft_unset(cmd->content->cmd);
	// else if (cmd->content->cmd_type == 8)
	// 	ft_env(cmd->content->cmd);
	return (0);
}

int	ft_processes(t_prog *msh)
{
	t_list	*temp;

	temp = msh->cmds->next;
	while (temp)
	{
		if (temp->content->cmd_type == 9)
			return (1);
		if (temp->content->cmd_type < 3)
			fork_process(temp, msh->envp);
		else
			ft_builtin(temp);
		dup2(msh->dup_fd_stdout, STDOUT_FILENO);
		temp = temp->next;
	}
	return (0);
}

int	wait_children(t_prog *msh)
{
	t_list	*temp;
	
	temp = msh->cmds->next;
	while (temp)
	{
		printf("OKKKKK\n");
		waitpid(temp->content->pid, NULL, 0);
		temp = temp->next;
	}
	return (0);
}

int	ft_process_line(char *line, t_prog *minishell)
{
	int	tmp;
	printf("\033[0;37m");
	add_history(line);
	line = replace_var(line, minishell);
	if (ft_parsing(line, minishell) == -1)
		return (-1);
    // check cmds with access ; if -1 -> not valid, 1 -> absolute path, 2 -> env cmd (comme ls), >= 3 -> builtin
	ft_check_cmds(minishell);
    // set pipes with fds && fork processes avec distinction entre builtins et cmds
	tmp = ft_processes(minishell);
	if (tmp == -1 || tmp == 1)
		return (tmp);
	// // wait pour tous les pids
	wait_children(minishell);
	return (0);
}
