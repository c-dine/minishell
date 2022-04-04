/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:50:55 by ntan              #+#    #+#             */
/*   Updated: 2022/04/04 15:52:06 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**add_to_env_tab(char **tab, char *var, int tmp)
{
	int	i;
	int	size_var_name;

	size_var_name = 0;
	while (var[size_var_name] && var[size_var_name] != '=')
		size_var_name++;
	if (ft_is_in_tab(var, tab, tmp) == 0)
		return (add_to_duotab(tab, var));
	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], var, size_var_name + 1) == 0)
			break ;
		i++;
	}
	tab[i] = ft_strdup(var);
	return (tab);
}

char	*ft_unquote(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	i++;
	if (var[i] == '"')
	{
		while (var[i + 1] != '"')
		{
			var[i] = var[i + 1];
			i++;
		}
		var[i] = '\0';
	}
	return (var);
}

char	*ft_quote(char *var)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (var[i + 1])
	{
		if (var[i] == '=' && var[i + 1] == '"')
			return (var);
		i++;
	}
	mempush(&res, sizeof(char), ft_strlen(var) + 3);
	i = 0;
	j = 0;
	while (var[i] != '=')
		res[j++] = var[i++];
	res[j++] = var[i++];
	res[j++] = '"';
	while (var[i])
		res[j++] = var[i++];
	res[j++] = '"';
	res[j] = '\0';
	return (res);
}

char	*remove_plus(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '+')
		{
			while (var[i + 1])
			{
				var[i] = var[i + 1];
				i++;
			}
			var[i] = '\0';
			break ;
		}
		i++;
	}
	return (var);
}

char	**cat_to_env_tab(char **tab, char *var, int tmp)
{
	int	i;
	int	size_var_name;

	size_var_name = 0;
	while (var[size_var_name] && var[size_var_name] != '=')
		size_var_name++;
	if (ft_is_in_tab(var, tab, tmp) == 0)
		return (add_to_duotab(tab, var));
	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], var, size_var_name + 1) == 0)
			break ;
		i++;
	}
	tab[i] = ft_strjoin(tab[i], &var[size_var_name + 1]);
	return (tab);
}
