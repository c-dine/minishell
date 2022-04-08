/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:19:17 by ntan              #+#    #+#             */
/*   Updated: 2022/04/08 16:52:20 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*free_buf_hd(char *buf)
{
	char	*tmp;

	tmp = ft_strdup(buf);
	free(buf);
	return (tmp);
}

char	*replace_var_hd(char *line, t_prog *msh)
{
	char	*res;

	// if (check_single_quote(line) == -1)
	// 	return (NULL);
	mempush(&res, sizeof(char), get_size_with_vars(line, msh) + 2);
	alias_expansion(line, res, msh, 1);
	return (remove_first_spaces(res));
}

int	heredoc_prompt(t_heredoc *heredoc, char *delim, t_prog *msh)
{
	char	*buf;
	char	*res;
	int		save_in;

	save_in = dup(STDIN_FILENO);
	res = "";
	while (1)
	{
		buf = readline("heredoc> ");
		if (buf == NULL)
		{
			if (g_error_code == 130)
				return (ctrlc_heredoc(save_in));
			ft_error(BASH_WARNING, hd_error(delim), 0);
			break ;
		}
		buf = free_buf_hd(buf);
		if (ft_strncmp(delim, buf, ft_strlen(buf)) == 0
			&& ft_strlen(buf) == ft_strlen(delim))
			break ;
		if (heredoc->expand == 1)
			buf = replace_var_hd(buf, msh);
		res = hd_strjoin(res, buf);
	}
	return (heredoc->str = res, close(save_in), 0);
}

void	*print_heredoc(char *str, t_heredoc *heredoc, t_prog *msh)
{
	int		i;
	char	*delim;

	i = 1;
	delim = NULL;
	while (str[i])
	{
		if (str[i] == '<' && str[i - 1] == '<')
		{
			delim = find_delim(&str[i], heredoc);
			rm_end_spaces(delim);
			if (delim == NULL)
				return (ft_error(PARSE_ERROR,
						"no heredoc delimiter", 2), NULL);
			if (heredoc_prompt(heredoc, delim, msh) == 1)
				return (NULL);
		}
		i++;
	}
	return ((void *)1);
}

t_heredoc	*add_heredoc(t_list *cmd, t_prog *msh)
{
	t_heredoc	*heredoc;
	char		*hd_pos;

	mempush(&heredoc, sizeof(*heredoc), 1);
	heredoc->fd = -1;
	heredoc->expand = 1;
	hd_pos = find_heredoc((char *)cmd->content);
	if (hd_pos == NULL)
		return (heredoc);
	if (print_heredoc((char *)cmd->content, heredoc, msh) == NULL)
		return (NULL);
	return (heredoc);
}

void	*ft_heredoc(t_prog *msh)
{
	t_hd_list	*temp2;
	t_list		*temp;

	temp = msh->cmds->next;
	temp2 = hd_lstnew(NULL);
	msh->heredocs = temp2;
	while (temp)
	{
		signal(SIGINT, signal_heredoc);
		temp2->next = hd_lstnew(add_heredoc(temp, msh));
		signal(SIGINT, signal_manager);
		if (temp2->next->content == NULL)
			return (NULL);
		temp = temp->next;
		temp2 = temp2->next;
	}
	return ((void *)1);
}
