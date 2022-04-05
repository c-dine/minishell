/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:18:08 by cdine             #+#    #+#             */
/*   Updated: 2022/04/05 19:24:05 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	size_if_dollar_sign(int *i, int *extra_size, t_prog *msh, char *line)
{
	if (line[*i + 1] == '?')
	{
		*extra_size += - (2 - ft_nblen(msh->prev_err_code));
		*i += 1;
	}
	else if (line[*i + 1] == ' ' || line[*i + 1] == '\0')
		(*i)++;
	else if (line[*i + 1] == '\'' || line[*i + 1] == '"')
	{
		(*i)++;
		(*extra_size)--;
	}
	else if (ft_isalpha(line[*i + 1]) == 0)
	{
		*extra_size = -2;
		*i += 2;
	}
	else
	{
		*extra_size += get_size_var(&line[*i], msh);
		(*i)++;
		while (line[*i] && ft_isalnum(line[*i]) == 1)
			(*i)++;
	}
}

int	size_if_backslash(int *open_d_quote, int *i, char *line)
{
	(*i)++;
	if (*open_d_quote % 2 == 1)
		return (0);
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] != '\'')
		return (-1);
	(*i)++;
	return (0);
}

// donne taille TOTALE a malloc pour la nouvelle chaine de char avec les vars
int	get_size_with_vars(char *line, t_prog *msh)
{
	int	i;
	int	extra_size;
	int	open_d_quote;

	open_d_quote = 0;
	i = 0;
	extra_size = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			open_d_quote++;
			i++;
		}
		else if (line[i] == '\'')
			size_if_backslash(&open_d_quote, &i, line);
		else if (line[i] == '$')
			size_if_dollar_sign(&i, &extra_size, msh, line);
		else
			i++;
	}
	return (i + extra_size);
}
