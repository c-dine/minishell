/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:56:11 by cdine             #+#    #+#             */
/*   Updated: 2022/04/05 19:24:02 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	if_single_dollar_sign(t_index *i, char *res, char *line, t_prog *msh)
{
	char	*tmp;
	int		k;

	tmp = get_var_content(&line[i->i], msh);
	if (tmp == NULL)
	{
		(i->i)++;
		while (line[i->i] && ft_isalnum(line[i->i]) == 1)
			(i->i)++;
	}
	else
	{
		k = 0;
		while (tmp[k])
			res[(i->j)++] = tmp[k++];
		(i->i)++;
		while (line[i->i] && ft_isalnum(line[i->i]) == 1)
			(i->i)++;
	}
}

void	if_dollar_sign(t_index *i, char *res, char *line, t_prog *msh)
{
	char	*tmp;
	int		k;

	if (line[i->i + 1] == '?')
	{
		k = 0;
		tmp = ft_itoa(msh->prev_err_code);
		while (k < ft_nblen(msh->prev_err_code))
			res[(i->j)++] = tmp[k++];
		i->i += 2;
		free(tmp);
	}
	else if (line[i->i + 1] == ' ' || line[i->i + 1] == '\0')
		res[(i->j)++] = line[(i->i)++];
	else if (line[i->i + 1] == '\'' || line[i->i + 1] == '"')
		(i->i)++;
	else if (ft_isalpha(line[i->i + 1]) == 0)
		i->i += 2;
	else
		if_single_dollar_sign(i, res, line, msh);
}

int	if_backslash(t_index *i, int *open_d_quote, char *res, char *line)
{
	res[i->j++] = line[i->i++];
	if (*open_d_quote % 2 == 1)
		return (0);
	while (line[i->i] && line[i->i] != '\'')
		res[i->j++] = line[i->i++];
	res[i->j++] = line[i->i++];
	return (0);
}

void	alias_expansion(char *line, char *res, t_prog *msh)
{
	t_index	i;
	int		open_d_quote;

	open_d_quote = 0;
	i.i = 0;
	i.j = 0;
	while (line[i.i])
	{
		if (line[i.i] == '"')
		{
			open_d_quote++;
			res[i.j++] = line[i.i++];
		}
		else if (line[i.i] == '\'')
			if_backslash(&i, &open_d_quote, res, line);
		else if (line[i.i] == '$')
			if_dollar_sign(&i, res, line, msh);
		else if (line[i.i])
			res[i.j++] = line[i.i++];
	}
	res[i.j] = '\0';
}
