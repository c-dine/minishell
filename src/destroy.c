/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:35:12 by ntan              #+#    #+#             */
/*   Updated: 2022/03/22 23:21:44 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipe(int *fd)
{
	if (fd && fd[0] != -1)
		close(fd[0]);
	if (fd && fd[1] != -1)
		close(fd[1]);
}

void	close_fd_tab(char **trioput, int *fd)
{
	int	i;

	i = 0;
	while (i < strlen_duotab(trioput))
	{
		if (fd[i] != -1)
			close(fd[i]);
		i++;
	}
}

void	close_fds(t_prog *msh)
{
	t_list		*tmp;

	tmp = msh->cmds->next;
	while (tmp)
	{
		// printf("INPUT CLOSE\n");
		// print_duotab(tmp->content->input);
		// printf("OUTPUTPUT CLOSE\n");
		// print_duotab(tmp->content->output);
		if (tmp->content->input_fd)
			close_fd_tab(tmp->content->input, tmp->content->input_fd);
		if (tmp->content->output_fd)
			close_fd_tab(tmp->content->output, tmp->content->output_fd);
		if (tmp->content->outputs_append_fds)
			close_fd_tab(tmp->content->outputs_append,
				tmp->content->outputs_append_fds);
		if (tmp->content->pipe)
			close_pipe(tmp->content->pipe);
		tmp = tmp->next;
	}
}

void	set_err_status(int code, char *str)
{
	printf("%s\n", str);
	error_code = code;
}

void	*ft_error(int code)
{
	if (code == CMD_NOT_FOUND)
		set_err_status(127, "minishell: command not found (RTFM)");
	else if (code == FILE_NOT_FOUND)
		set_err_status(1, "minishell: no such file or directory");
	else if (code == QUOTE_NOT_CLOSED)
		set_err_status(1, "minishell: quote not closed");
	else if (code == PARSE_ERROR)
		set_err_status(0, "minishell: parse error");
	else if (code == PERMISSION_DENIED)
		set_err_status(0, "minishell: permission denied");
	return (NULL);
}