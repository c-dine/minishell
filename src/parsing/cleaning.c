/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:57:34 by ntan              #+#    #+#             */
/*   Updated: 2022/04/06 16:57:20 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_cmd_3(t_block *res, t_prog *msh, char *str)
{
	int	i;

	res->cmd = ft_split(str, ' ');
	i = 0;
	while (res->cmd[i])
	{
		res->cmd[i] = ft_quotes(replace_var(res->cmd[i], msh));
		i++;
	}
	res->cmd = remove_empty_cmd(res->cmd, i);
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

void	clean_cmd(t_block *res, char *str, t_prog *msh)
{
	int	i;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (str[i] == '"')
				d_quote++;
			else if (str[i] == '\'')
				s_quote++;
			i++;
		}
		// if (str[i] == '"')
		// {
		// 	i++;
		// 	d_quote++;
		// }
		// if (str[i] == '\'')
		// {
		// 	i++;
		// 	s_quote++;
		// }
		if (d_quote % 2 == 0 && s_quote % 2 == 0
			&& (str[i] == '<' || str[i] == '>'))
			clean_cmd_2(str, &i);
		else if (str[i])
			i++;
	}
	clean_cmd_3(res, msh, str);
	// res->cmd = ft_split(str, ' ');
	// i = 0;
	// while (res->cmd[i])
	// {
	// 	res->cmd[i] = ft_quotes(replace_var(res->cmd[i], msh));
	// 	i++;
	// }
	// res->cmd = remove_empty_cmd(res->cmd, i);
}
