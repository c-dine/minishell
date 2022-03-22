/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:19:17 by ntan              #+#    #+#             */
/*   Updated: 2022/03/22 17:14:06 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_heredoc(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (i >= 1)
	{
		if (str[i] == '<' && str[i - 1] == '<')
			return (&str[i]);
		i--;
	}
	return (NULL);
}

void fill_heredoc(t_heredoc heredoc, char *str)

t_heredoc add_heredoc(t_list *cmd)
{
	t_heredoc	heredoc;
	char		*hd_pos;
	heredoc.fd = -1;
	hd_pos = find_heredoc((char *) cmd->content);
	if (hd_pos == NULL)
		return(heredoc);
	else
		fill_heredoc(heredoc, hd_pos);
}

int	ft_heredoc(t_prog *msh)
{
	t_hd_list hd_list;
	t_hd_list *temp2;
	t_list *temp;

	temp = msh->cmds->next;
	while (temp)
	{
		temp2->content = add_heredoc();
		temp = temp->next;
		temp2 = temp2->next;
	}
}