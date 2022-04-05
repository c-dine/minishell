/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:23:00 by ntan              #+#    #+#             */
/*   Updated: 2022/04/05 17:54:50 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*cmd_to_block(t_list *cmd)
{
	t_block	*res;
	char	*str;
	int		i;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	str = (char *) cmd->content;
	i = 0;
	mempush(&res, sizeof(*res), 1);
	init_block(res);
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			d_quote++;
		}
		if (str[i] == '\'')
		{
			i++;
			s_quote++;
		}
		if (d_quote % 2 == 0 && s_quote % 2 == 0
			&& (str[i] == '<' || str[i] == '>'))
		{
			i++;
			if (parse_duoput(res, str, &i) == 1)
				return (ft_error(PARSE_ERROR, "minishell", 2), NULL);
		}
		else if (str[i])
			i++;
	}
	res->input_type = find_input_type(str);
	res->output_type = find_output_type(str);
	clean_cmd(res, str);
	cmd->content = res;
	return (str);
}

int	parse_cmd(t_prog *msh)
{
	t_list		*temp;
	t_hd_list	*temp_hd;
	int			cmd_i;

	cmd_i = 0;
	temp = msh->cmds->next;
	if (ft_heredoc(msh) == NULL)
		return (-1);
	temp_hd = msh->heredocs->next;
	while (temp)
	{
		if (cmd_to_block(temp) == NULL)
			return (-1);
		temp->content->cmd_i = cmd_i;
		if (open_pipes(temp->content) == 1)
			return (-1);
		temp->content->heredoc = temp_hd->content;
		temp->content->pid = -2;
		temp_hd = temp_hd->next;
		temp = temp->next;
		cmd_i++;
	}
	return (0);
}

int	ft_check_pipe_parse_error(char *line)
{
	int	i;
	int	tmp;
	int	pipe;

	i = 0;
	pipe = 0;
	tmp = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '|')
			tmp++;
		if (line[i] == '|' && pipe == 0)
			pipe++;
		if (line[i] == '|' && pipe == 1 && tmp == 0)
			return (1);
		else if (line[i] == '|' && pipe == 1 && tmp != 0)
			tmp = 0;
		i++;
	}
	return (0);
}

int check_multiple_chevrons(char *line)
{
	int	i;

	i = 2;
	while (line[i])
	{
		if ((line[i] == '<' || line[i] == '>')
			&& (line[i - 1] == '<' || line[i - 1] == '>')
			&& (line[i - 2] == '<' || line[i - 2] == '>'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_parsing(char *line, t_prog *minishell)
{
	char	**split_line;
	int		i;
	t_list	*temp;
 
	if (ft_check_pipe_parse_error(line) == 1
		|| (ft_strlen(line) > 2 && check_multiple_chevrons(line) == 1))
		return (ft_error(PARSE_ERROR, "minishell", 2), -1);
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
