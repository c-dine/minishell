/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:35:12 by ntan              #+#    #+#             */
/*   Updated: 2022/03/26 18:09:17 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_pipes(t_list *beg_all_pipes, int fd1, int fd2)
{
	t_list	*temp;

	(void) fd1;
	(void) fd2;
	// ferme tous les fd sauf fd1 et fd2 (??)
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

void	close_main_process(t_list *node)
{
	if (node->content->cmd_i != 0)
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
	if (indic_type != CMD_NOT_FOUND)
		printf("minishell: ");
	if (indic)
		printf("%s", indic);
	if (indic_type == INVALID_IDENTIFIER)
		printf("\': ");
	else
		printf(": ");
	printf("%s", str);
	printf("\n");
	error_code = code;
}

void	*ft_error(int code, char *indic)
{
	if (code == CMD_NOT_FOUND)
		set_err_status(127, "command not found (RTFM)", indic, code);
	else if (code == FILE_NOT_FOUND)
		set_err_status(1, "No such file or directory", indic, code);
	else if (code == QUOTE_NOT_CLOSED)
		set_err_status(1, "quote not closed", indic, code);
	else if (code == PARSE_ERROR)
		set_err_status(0, "parse error", indic, code);
	else if (code == PERMISSION_DENIED)
		set_err_status(0, "Permission denied", indic, code);
	else if (code == INVALID_IDENTIFIER)
		set_err_status(1, "not a valid identifier", indic, code);
	else if (code == INVALID_DIRECTORY)
		set_err_status(1, "Not a directory", indic, code);
	return (NULL);
}