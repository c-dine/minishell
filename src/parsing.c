/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:23:00 by ntan              #+#    #+#             */
/*   Updated: 2022/03/10 23:1604:04 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_input(t_block *res, char *str, int *i)
{
	int 	marker;
	int		tmp;
	char	*temp;

	tmp = 0;
	if (str[*i - 1] == '>')
		tmp = 1;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == '|' || str[*i] == '>'
		|| str[*i] == '<' || str[*i] == '\0')
		return (1);
	marker = *i;
	while (str[*i] && str[*i] != ' ')
		(*i)++;
	mempush(&temp, sizeof(char), *i - marker + 1);
	ft_strlcpy(temp, &str[marker], *i - marker + 1);
	if (tmp == 0)
		res->input = temp;
	else
		res->output = temp;
	return (0);
}

void	cmd_to_block(t_list *cmd)
{
	t_block	*res;
	char 	*str;
	int		i;

	str = (char *) cmd->content;
	i = 0;
	mempush(&res, sizeof(*res), 1);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i++;
			if (parse_input(res, str, &i) == 1)
			{
				printf("AAAAAAAAAAH\n");
				break ;
			}
		}
		else
			i++;
	}
	printf("input : %s\n", res->input);
	printf("cmd : %s\n", res->cmd);
	printf("output : %s\n\n", res->output);
	cmd->content = res;
}

/** msh = minishell raccourci**/
void	parse_cmd(t_prog *msh)
{
	t_list	*temp;

	temp = msh->cmds->next;
	while (temp)
	{
		printf("parse : %s\n", (char *)temp->content);
		cmd_to_block(temp);
		temp = temp->next;
	}
}


void	ft_process_line(char *line, t_prog *minishell)
{
	char	**split_line;
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
	parse_cmd(minishell);
	// open_pipe(minishell);
}



