/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:18:08 by cdine             #+#    #+#             */
/*   Updated: 2022/03/16 22:40:53 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// renvoie contenu de la variable depuis env
char	*get_var_content(char *line, t_prog *msh)
{
	int	i;
	int	j;
	int	k;
	int	size_var;

	size_var = 1;
	while (line[size_var] && ft_isalnum(line[size_var]) == 1)
		size_var++;
	i = 0;
	while (msh->envp[i])
	{
		j = 0;
		k = 1;
		while (msh->envp[i][j] && msh->envp[i][j] != '=' && ft_isalnum(line[k]) == 1)
		{
			if (ft_strncmp(msh->envp[i], &line[1], k) != 0)
				break ;
			k++;
			j++;
		}
		if (msh->envp[i][j] == '=' && j == size_var - 1)
			return (&msh->envp[i][size_var]);
		i++;
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

// donne taille TOTALE a malloc pour la nouvelle chaine de char avec les vars
int	get_size_with_vars(char *line, t_prog *msh)
{
	int	i;
	int	extra_size;

	i = 0;
	extra_size = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] != '\'')
				return (-1);
		}
		if (line[i] == '$')
		{
			extra_size += get_size_var(&line[i], msh);
			while (line[i] && line[i] != ' ' && line[i] != '<'
				&& line[i] != '>' && line[i] != '|')
				i++;
		}
		else
			i++;
	}
	return (i + extra_size);
}

void	alias_expansion_single_quote(char *res, char *line, int *j, int *i)
{
	res[(*j)++] = line[(*i)++];
	while (line[(*i)] && line[(*i)] != '\'')
		res[(*j)++] = line[(*i)++];
	res[(*j)++] = line[(*i)++];
}

void	alias_expansion(char *line, char *res, t_prog *msh)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			alias_expansion_single_quote(res, line, &j, &i);
		if (line[i] == '$')
		{
			tmp = get_var_content(&line[i], msh);
			if (tmp == NULL)
			{
				while (line[i] && line[i] != ' ' && line[i] != '<'
					&& line[i] != '>' && line[i] != '|')
					i++;
			}
			else
			{
				k = 0;
				while (tmp[k])
					res[j++] = tmp[k++];
				i++;
				while (line[i] && ft_isalnum(line[i]) == 1)
					i++;
			}
		}
		else if (line[i])
			res[j++] = line[i++];
	}
	res[j] = '\0';
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

char	*replace_var(char *line, t_prog *msh)
{
	char	*res;

	if (check_single_quote(line) == -1)
		return (NULL);
	mempush(&res, sizeof(char), get_size_with_vars(line, msh) + 1);
	alias_expansion(line, res, msh);
	return (res);
}