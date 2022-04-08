/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiputing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:00:13 by ntan              #+#    #+#             */
/*   Updated: 2022/04/08 12:37:16 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*parse_duoput_2(char *str, int *i)
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
	return (temp);
}

int	parse_duoput(t_block *res, char *str, int *i, t_prog *msh)
{
	int		tmp;
	char	*temp;

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
	temp = parse_duoput_2(str, i);
	parse_duoput_3(tmp, msh, res, temp);
	return (0);
}

int	find_output_type(char *cmd)
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

int	find_input_type(char *cmd)
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
