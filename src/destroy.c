/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:35:12 by ntan              #+#    #+#             */
/*   Updated: 2022/04/03 15:17:18 by cdine            ###   ########.fr       */
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

void	set_err_status(int code, char *str, char *indic, int indic_type)
{
	if (indic_type != CMD_NOT_FOUND && indic_type != QUOTE_NOT_CLOSED
		&& ft_strncmp(indic, "minishell", 10) != 0)
		write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	if (indic)
		write(STDERR_FILENO, indic, ft_strlen(indic));
	if (indic_type == INVALID_IDENTIFIER)
		write(STDERR_FILENO, "\': ", ft_strlen("\': "));
	else
		write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	error_code = code;
}

void	*ft_error(int code, char *indic, int err_code)
{
	if (code == CMD_NOT_FOUND)
		set_err_status(err_code, "command not found (RTFM)", indic, code);
	else if (code == FILE_NOT_FOUND)
		set_err_status(err_code, "No such file or directory", indic, code);
	else if (code == QUOTE_NOT_CLOSED)
		set_err_status(err_code, "quote not closed", indic, code);
	else if (code == PARSE_ERROR)
		set_err_status(err_code, "parse error", indic, code);
	else if (code == PERMISSION_DENIED)
		set_err_status(err_code, "Permission denied", indic, code);
	else if (code == INVALID_IDENTIFIER)
		set_err_status(err_code, "not a valid identifier", indic, code);
	else if (code == INVALID_DIRECTORY)
		set_err_status(err_code, "Not a directory", indic, code);
	else if (code == PATH_CORRUPTED)
		set_err_status(err_code, "path corrupted", indic, code);
	else if (code == FORK_ERROR)
		set_err_status(err_code, "error", indic, code);
	else if (code == TOO_MANY_FDS)
		set_err_status(err_code, "Too many open files", indic, code);
	else if (code == BASH_WARNING)
		set_err_status(err_code, "", indic, code);
	else if (code == FILENAME_REQUIRED)
		set_err_status(err_code, "filename argument required", indic, code);
	return (NULL);
}