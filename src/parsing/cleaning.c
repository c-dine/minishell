/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:57:34 by ntan              #+#    #+#             */
/*   Updated: 2022/04/05 17:53:09 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*copy_no_quotes(char *str, int size)
{
	char	*res;
	int		j;
	int		i;

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
	int	i;
	int	size;

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

void	clean_cmd_2(char *str, int *i)
{
	str[(*i)++] = ' ';
	if (str[*i] == '>' || str[*i] == '<')
		str[(*i)++] = ' ';
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == '"')
	{
		str[*i] = ' ';
		while (str[++(*i)] && str[*i] != '"')
			str[*i] = ' ';
		str[*i] = ' ';
	}
	else if (str[*i] == '\'')
	{
		str[*i] = ' ';
		while (str[++(*i)] && str[*i] != '\'')
			str[*i] = ' ';
		str[*i] = ' ';
	}
	else
	{
		while (str[*i] && str[*i] != '|' && str[*i] != ' ')
			str[(*i)++] = ' ';
	}
}

void	clean_cmd(t_block *res, char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	i = 0;
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
			clean_cmd_2(str, &i);
		else if (str[i])
			i++;
	}
	res->cmd = ft_split(str, ' ');
	i = 0;
	while (res->cmd[i])
	{
		res->cmd[i] = ft_quotes(res->cmd[i]);
		i++;
	}
}
