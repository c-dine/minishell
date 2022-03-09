/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:23:00 by ntan              #+#    #+#             */
/*   Updated: 2022/03/09 00:23:00 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_process_line(char *line, t_prog *minishell)
{
	char 	**split_line;

	printf("\033[0;37m");
	split_line = ft_split(line, '|');
	if (split_line == NULL)
		exit(1);
	minishell->cmd_tab = split_line;

	// int		i;
	// i = 0;
	// while(split_line[i])
	// {
	// 	temp.content.cmd = ft_lstnew(split_line[i]);
	// 	if (i == 0)
	// 		minishell->list->content = temp;
	// 	else
	// 		ft_lstadd_back(&minishell->list, temp);
	// 	i++;
	// }
}
