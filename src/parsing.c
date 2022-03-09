/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:23:00 by ntan              #+#    #+#             */
/*   Updated: 2022/03/09 18:38:41 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_process_line(char *line, t_prog *minishell)
{
	char 	**split_line;
	int		i;
	t_list	*temp;
	t_list	*begin;

	printf("\033[0;37m");
	split_line = ft_split(line, '|');
	if (split_line == NULL)
		exit(1);
	// minishell->cmd_tab = split_line;

	temp = ft_lstnew(0);
	begin = temp;
	i = 0;
	while (split_line[i])
	{
		temp->next = ft_lstnew(split_line[i]);
		free(split_line[i]);
		temp = temp->next;
		i++;
	}
	free(split_line);
	free(line);
	minishell->list = begin;
}
