/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:23:00 by ntan              #+#    #+#             */
/*   Updated: 2022/03/10 19:01:18 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_process_line(char *line, t_prog *minishell)
{
	char 	**split_line;
	int		i;
	t_list	*temp;

	printf("\033[0;37m");
	split_line = ft_split(line, '|');
	if (split_line == NULL)
		exit(1);
	temp = ft_lstnew(NULL);
	minishell->cmds = temp;
	i = 0;
	while (split_line[i])
	{
		temp->next = ft_lstnew(split_line[i]);
		temp = temp->next;
		i++;
	}
	free(line);
}
