/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:23:00 by ntan              #+#    #+#             */
/*   Updated: 2022/04/03 16:19:59 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_no_quotes(char *str, int size)
{
	char *res;
	int j;
	int i;
	
	// res = malloc(sizeof(char) * (size + 1));
	mempush(&res, sizeof(char), (size + 1));
	i = 0;
	j = 0;
	while (i < size)
	{
		if (str[i] != '\0')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*remove_quotes(char *str)
{
	int i;
	
	int size;

	size = ft_strlen(str);
	i = 0;
	if (str[0] == '\"')
	{
		while (i < size)
		{
			if (str[i] && str[i] == '\"')
				str[i] = '\0';
			i++;
		}
	}
	else
	{
		while (i < size)
		{
			if (str[i] && str[i] == '\'')
				str[i] = '\0';
			i++;
		}
	}
	return (copy_no_quotes(str, size));
}

void clean_cmd(t_block *res, char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			str[i++] = ' ';
			if (str[i] == '>' || str[i] == '<')
				str[i++] = ' ';
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == '"')
			{
				str[i] = ' ';
				while (str[++i] && str[i] != '"')
					str[i] = ' ';
				str[i] = ' ';
			}
			else if (str[i] == '\'')
			{
				str[i] = ' ';
				while (str[++i] && str[i] != '\'')
					str[i] = ' ';
				str[i] = ' ';
			}
			else
			{
				while (str[i] && str[i] != '|' && str[i] != ' ')
					str[i++] = ' ';
			}
		}
		else
			i++;
	}
	res->cmd = ft_split(str, ' ');
	// if (ft_strncmp(res->cmd[0], "cat", 3) == 0)
	// 	res->sig_status = 1;
	i = 0;
	while (res->cmd[i])
	{
		res->cmd[i] = ft_quotes(res->cmd[i]);
		i++;
	}
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
	if (str[*i - 1] == '<' && str[*i] == '<')
		tmp = 3;
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
		res->input = add_to_duotab(res->input, ft_quotes(temp));
	else if (tmp == 1)
		res->output = add_to_duotab(res->output, ft_quotes(temp));
	else if (tmp == 2)
		res->outputs_append = add_to_duotab(res->outputs_append, ft_quotes(temp));
	else if (tmp == 3) // EN CAS DE HEREDOC ON PASSE INPUT EN TYPE 2
		res->input_type = 2;
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
	res->sig_status = 0;
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
				return (ft_error(PARSE_ERROR, "minishell", 2), NULL);
		}
		else
			i++;
	}
	res->input_type = find_input_type(str);
	res->output_type = find_output_type(str);
	clean_cmd(res, str);
	cmd->content = res;
	return (str);
}

/** msh = minishell raccourci**/
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
		// printf("heredoc str : %s\n", temp->content->heredoc->str);
		// printf("CMD:\n");
		// print_duotab(temp->content->cmd);
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

int	ft_parsing(char *line, t_prog *minishell)
{
	char	**split_line;
	int		i;
	t_list	*temp;

	if (ft_check_pipe_parse_error(line) == 1)
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
