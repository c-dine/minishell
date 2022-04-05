/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:42:41 by cdine             #+#    #+#             */
/*   Updated: 2022/04/05 19:02:25 by cdine            ###   ########.fr       */
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
	if (WCOREDUMP(err) && WTERMSIG(err) == 3)
	{
		g_error_code = 131;
		printf("Quit (core dumped)\n");
	}
	if (WCOREDUMP(err) && WTERMSIG(err) == 11)
	{
		g_error_code = 139;
		printf("Segmentation fault (core dumped)\n");
	}
	if (err != -1 && g_error_code == 0)
		g_error_code = WEXITSTATUS(err);
	return (0);
}

void	ft_close_builtin(int fd_out, t_list *cmd)
{
	close_trioput_fd(cmd);
	close(fd_out);
	close_main_process(cmd, 1);
}

void	no_cmd(t_list *cmd)
{
	open_fds(cmd->content);
	close_trioput_fd(cmd);
}

int	ft_check_specialchar(char *line)
{
	int	i;
	int	tmp;

	tmp = 0;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	if (line[i] == ':')
	{
		tmp++;
		g_error_code = 0;
	}
	if (line[i] == '!')
	{
		tmp++;
		g_error_code = 1;
	}
	i++;
	while (line[i] == ' ')
		i++;
	if (tmp == 1 && line[i] == '\0')
		return (1);
	return (0);
}
