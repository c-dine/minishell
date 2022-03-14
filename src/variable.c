/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:18:08 by cdine             #+#    #+#             */
/*   Updated: 2022/03/11 06:14:08 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// renvoie contenu de la variable depuis env
char	*get_var_content(char *line, t_prog *msh)
{
	int	i;
	int	j;
	int	size_var;

	size_var = 0;
	while (line[size_var] && line[size_var] != ' ' && line[size_var] != '<'
		&& line[size_var] != '>' && line[size_var] != '|')
		size_var++;
	i = 0;
	while (msh->envp[i])
	{
		j = 0;
		while (msh->envp[i][j] != '=')
		{
			if (ft_strncmp(msh->envp[i], &line[1], 1) == 0)
				return (&msh->envp[i][size_var]);
			j++;
		}
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
	while (line[size_var] && line[size_var] != ' ' && line[size_var] != '<'
		&& line[size_var] != '>' && line[size_var] != '|')
		size_var++;
	if (var_content == NULL)
		return (-size_var);
	while (var_content[size_content])
		size_content++;
	return (size_content - size_var);
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
			while (line[++i] != '\'')
				i++;
			if (line[i] != '\'')
				return (-1);
			i++;
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
	while (line[(*i)] != '\'')
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
				while (line[i] && line[i] != ' ' && line[i] != '<'
					&& line[i] != '>' && line[i] != '|')
					i++;
			}
		}
		else
			res[j++] = line[i++];
	}
	res[j] = '\0';	
}
//////////////// NE MARCHE PAS QUAND VARIABLE COLLEE A UN AUTRE CHAR AUTRE QUE ' '
char	*replace_var(char *line, t_prog *msh)
{
	int	size_to_alloc;
	char	*res;

	size_to_alloc = get_size_with_vars(line, msh);
	if (size_to_alloc == -1)
		return (NULL);
		// return error de single quote pas fermee --> indetermine
	mempush(&res, sizeof(char), size_to_alloc + 1);
	alias_expansion(line, res, msh);
	return (res);
}