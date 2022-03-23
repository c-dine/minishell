/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:23:00 by ntan              #+#    #+#             */
/*   Updated: 2022/03/23 18:21:38 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void clean_cmd(t_block *res, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			str[i++] = ' ';
			if (str[i] == '>')
				str[i++] = ' ';
			while (str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ' && str[i] != '|')
				str[i++] = ' ';
		}
		else
			i++;
	}
	res->cmd = ft_split(str, ' ');
}

int	parse_duoput(t_block *res, char *str, int *i)
{
	int 	marker;
	char	*temp;
	int		tmp;

	tmp = 0;
	if (str[*i - 1] == '>') /**OUTPUT**/
		tmp = 1;
	if (str[*i - 1] == '>' && str[*i] == '>') /**APPEND**/
	{
		(*i)++;
		tmp = 2;
	}	
	// if (str[*i - 1] == '<' && str[*i] == '<')
	// 	tmp = 3;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == '|' || (str[*i] == '>' && str[*i - 1] != '>')
		|| (str[*i] == '<' && str[*i - 1] != '<') || str[*i] == '\0')
		return (1);
	marker = *i;
	while (str[*i] && str[*i] != ' ')
	{
		(*i)++;
		if (str[*i] == '<' || str[*i] == '>')
			break ;
	}
	mempush(&temp, sizeof(char), *i - marker + 1);
	ft_strlcpy(temp, &str[marker], *i - marker + 1);
	if (tmp == 0)
		res->input = add_to_duotab(res->input, temp);
	else if (tmp == 1)
		res->output = add_to_duotab(res->output, temp);
	else if (tmp == 2)
		res->outputs_append = add_to_duotab(res->outputs_append, temp);
	// else if (tmp == 3)
	// 	printf("HEREDOC ICI\n");
	return (0);
}



void	init_block(t_block *res)
{
	mempush(&res->cmd, sizeof(char*), 1);
	mempush(&res->output, sizeof(char*), 1);
	mempush(&res->input, sizeof(char*), 1);
	mempush(&res->outputs_append, sizeof(char*), 1);
	res->cmd[0] = 0;
	res->input[0] = 0;
	res->output[0] = 0;
	res->outputs_append[0] = 0;
	res->input_fd = -2;
	res->output_fd = -2;
}

int find_output_type(char *cmd)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	while (cmd[i])
	{
		if (cmd[i] && (i >= 1 && cmd[i - 1]) && cmd [i] == '>' && (i >= 1 && cmd[i - 1] == '>'))
			type = 2;
		else if (cmd[i] && cmd [i] == '>')
			type = 1;
		i++;
	}
	return (type);
}

int find_input_type(char *cmd)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	while (cmd[i])
	{
		if (cmd[i] && (i >= 1 && cmd[i - 1]) && cmd [i] == '<' && (i >= 1 && cmd[i - 1] == '<'))
			type = 2;
		else if (cmd[i] && cmd [i] == '<')
			type = 1;
		i++;
	}
	return (type);
}

char *cmd_to_block(t_list *cmd)
{
	t_block	*res;
	char 	*str;
	int		i;

	str = (char *) cmd->content;
	i = 0;
	mempush(&res, sizeof(*res), 1);
	init_block(res);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i++;
			if (parse_duoput(res, str, &i) == 1)
				return (ft_error(PARSE_ERROR, NULL), NULL);
		}
		else
			i++;
	}
	res->input_type = find_input_type(str);
	res->output_type = find_output_type(str);
	clean_cmd(res, str);
	open_pipes(res);
	cmd->content = res;
	return (str);
}



/** msh = minishell raccourci**/
int	parse_cmd(t_prog *msh)
{
	t_list	*temp;

	temp = msh->cmds->next;
	//lancer les heredoc -> param (liste chaines de commandes)
	while (temp)
	{
		if (cmd_to_block(temp) == NULL)
			return (-1);
		temp->content->pid = -2;
		temp = temp->next;
	}
	return (0);
}


int	ft_parsing(char *line, t_prog *minishell)
{
	char	**split_line;
	int		i;
	t_list	*temp;

	split_line = ft_split(line, '|');
	if (split_line == NULL)
		return (-1);
	temp = ft_lstnew(NULL);
	minishell->cmds = temp;
	i = 0;
	while (split_line[i])
	{
		temp->next = ft_lstnew(split_line[i]);
		temp = temp->next;
		i++;
	}
	if (parse_cmd(minishell) == -1)
		return (-1);
	return (0);
}
