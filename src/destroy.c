/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:35:12 by ntan              #+#    #+#             */
/*   Updated: 2022/03/25 18:42:53 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_pipes(t_list *beg_all_pipes, int fd1, int fd2)
{
	t_list	*temp;

	// ferme tous les fd sauf fd1 et fd2 (??)
	temp = beg_all_pipes;
	while (temp)
	{
		if (temp->content->pipe[0] != fd1 && temp->content->pipe[0] != fd2)
			close(temp->content->pipe[0]);
		if (temp->content->pipe[1] != fd1 && temp->content->pipe[1] != fd2)
			close(temp->content->pipe[1]);
		temp = temp->next;
	}
}

void	close_trioput_fd(t_list *cmd)
{
	if (cmd->content->input_fd != -2)
		close(cmd->content->input_fd);
	if (cmd->content->output_fd != -2)
		close(cmd->content->output_fd);
	if (cmd->content->input_type == 2)
		unlink(cmd->content->heredoc->temp);
}

void	set_err_status(int code, char *str, char *indic)
{
	printf("minishell: ");
	if (indic)
		printf("'%s': ", indic);
	printf("%s\n", str);
	error_code = code;
}

void	*ft_error(int code, char *indic)
{
	if (code == CMD_NOT_FOUND)
		set_err_status(127, "command not found (RTFM)", NULL);
	else if (code == FILE_NOT_FOUND)
		set_err_status(1, "no such file or directory", NULL);
	else if (code == QUOTE_NOT_CLOSED)
		set_err_status(1, "quote not closed", NULL);
	else if (code == PARSE_ERROR)
		set_err_status(0, "parse error", NULL);
	else if (code == PERMISSION_DENIED)
		set_err_status(0, "permission denied", NULL);
	else if (code == INVALID_IDENTIFIER)
		set_err_status(1, "not a valid identifier", indic);
	return (NULL);
}