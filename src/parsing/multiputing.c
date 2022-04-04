/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiputing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:00:13 by ntan              #+#    #+#             */
/*   Updated: 2022/04/04 15:01:12 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parse_duoput_2(t_block *res, char *str, int *i, char tmp)
{
	int		marker;
	char	*temp;

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
		res->outputs_append = add_to_duotab(res->outputs_append,
				ft_quotes(temp));
	else if (tmp == 3)
		res->input_type = 2;
	return (0);
}

int	parse_duoput(t_block *res, char *str, int *i)
{
	int		tmp;

	tmp = 0;
	if (str[*i - 1] == '>')
		tmp = 1;
	if (str[*i - 1] == '>' && str[*i] == '>')
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
	parse_duoput_2(res, str, i, tmp);
	return (0);
}

void	init_block(t_block *res)
{
	mempush(&res->cmd, sizeof(char *), 1);
	mempush(&res->output, sizeof(char *), 1);
	mempush(&res->input, sizeof(char *), 1);
	mempush(&res->outputs_append, sizeof(char *), 1);
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
		if (cmd[i] && (i >= 1 && cmd[i - 1]) && cmd [i] == '>'
			&& (i >= 1 && cmd[i - 1] == '>'))
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
		if (cmd[i] && (i >= 1 && cmd[i - 1])
			&& cmd [i] == '<' && (i >= 1 && cmd[i - 1] == '<'))
			type = 2;
		else if (cmd[i] && cmd [i] == '<')
			type = 1;
		i++;
	}
	return (type);
}