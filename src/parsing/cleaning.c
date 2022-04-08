/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:57:34 by ntan              #+#    #+#             */
/*   Updated: 2022/04/08 16:51:40 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_add_oldcmd(char *cmd, t_prog *msh)
{
	char	**tmp;

	if (cmd && ft_count_cmds(msh) == 1)
	{
		tmp = NULL;
		mempush(&tmp, sizeof(char *), 3);
		tmp[0] = ft_strdup("export");
		tmp[1] = ft_strjoin("_=", cmd);
		tmp[2] = NULL;
		ft_export(tmp, msh);
	}
}

void	clean_cmd_3(t_block *res, t_prog *msh, char *str)
{
	int	i;
		
	res->cmd = ft_split(str, ' ');
	i = 0;
	while (res->cmd[i])
	{
		res->cmd[i] = replace_var(res->cmd[i], msh, 0);
		i++;
	}
	res->cmd = remove_empty_cmd(res->cmd, i);
	i = 0;
	while (res->cmd[i])
	{
		res->cmd[i] = ft_quotes(res->cmd[i]);
		i++;
	}
	if (i > 0)
		ft_add_oldcmd(res->cmd[i - 1], msh);
	else if (res->cmd[0])
		ft_add_oldcmd(res->cmd[0], msh);
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
			if (str[i] == '"' && s_quote % 2 == 0)
				d_quote++;
			else if (str[i] == '\'' && d_quote % 2 == 0)
				s_quote++;
			i++;
		}
		else if (d_quote % 2 == 0 && s_quote % 2 == 0
			&& (str[i] == '<' || str[i] == '>'))
			clean_cmd_2(str, &i);
		else if (str[i])
			i++;
	}
	clean_cmd_3(res, msh, str);
}
