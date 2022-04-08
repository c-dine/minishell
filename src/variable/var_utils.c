/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:59:26 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 12:25:39 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_first_spaces(char *str)
{
	int		i;
	int		j;
	int		d_quote;
	char	*res;

	res = ft_strdup(str);
	i = 0;
	j = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			d_quote++;
		if (str[i] == ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0')
			&& d_quote % 2 == 0)
			i++;
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	if (res[0] == ' ')
		return (&res[1]);
	return (res);
}

char	*replace_var(char *line, t_prog *msh)
{
	char	*res;

	if (check_single_quote(line) == -1)
		return (NULL);
	mempush(&res, sizeof(char), get_size_with_vars(line, msh) + 1);
	alias_expansion(line, res, msh);
	return (remove_first_spaces(res));
}

int	check_single_quote(char *line)
{
	int	i;
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			s_quote++;
		if (line[i] == '"')
			d_quote++;
		i++;
	}
	if (s_quote % 2 == 1 || d_quote % 2 == 1)
		return (-1);
	return (0);
}

// renvoie contenu de la variable depuis env
char	*get_var_content(char *line, t_prog *msh)
{
	t_index	i;
	int		k;
	int		size_var;

	size_var = 1;
	while (line[size_var] && (ft_isalnum(line[size_var]) == 1
			|| line[1] == '_'))
		size_var++;
	i.i = -1;
	while (msh->envp[++i.i])
	{
		i.j = 0;
		k = 1;
		while (msh->envp[i.i][i.j] && msh->envp[i.i][i.j] != '='
			&& (ft_isalnum(line[k]) == 1 || line[1] == '_'))
		{
			if (ft_strncmp(msh->envp[i.i], &line[1], k) != 0)
				break ;
			k++;
			i.j++;
		}
		if (msh->envp[i.i][i.j] == '=' && i.j == size_var - 1)
			return (&msh->envp[i.i][size_var]);
	}
	return (NULL);
}

// donne difference de taille entre $var et son contenu
int	get_size_var(char *line, t_prog *msh)
{
	int		size_var;
	int		size_content;
	char	*var_content;

	size_var = 0;
	size_content = 0;
	var_content = get_var_content(line, msh);
	while (line[size_var])
	{
		size_var++;
		if (size_var > 0 && ft_isalnum(line[size_var]) == 0)
			break ;
	}
	if (var_content == NULL)
		return (-size_var);
	while (var_content[size_content])
		size_content++;
	return (- (size_var - size_content));
}
