/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:18:02 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 13:29:13 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**cat_to_export_tab(char **export, char **envp, char *var)
{
	int	i;
	int	j;
	int	size_var_name;

	size_var_name = 0;
	while (var[size_var_name] && var[size_var_name] != '=')
		size_var_name++;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, size_var_name + 1) == 0)
			break ;
		i++;
	}
	if (ft_is_in_tab(var, export, 2) == 0)
		return (add_to_duotab(export, ft_quote(ft_strdup(envp[i]))));
	j = 0;
	while (export[j])
	{
		if (ft_strncmp(export[j], var, size_var_name + 1) == 0)
			break ;
		j++;
	}
	export[j] = ft_quote(ft_strdup(envp[i]));
	return (export);
}

int	ft_add_to_env(char *var, t_prog *msh, int tmp)
{
	if (tmp == 1)
	{
		if (ft_strncmp(var, "_=", 2) != 0)
			msh->export = add_to_env_tab(msh->export, ft_quote(var), tmp);
		msh->envp = add_to_env_tab(msh->envp, ft_unquote(var), tmp);
	}
	else if (tmp == 2)
	{
		msh->envp = cat_to_env_tab(msh->envp,
				ft_unquote(remove_plus(var)), tmp);
		msh->export = cat_to_export_tab(msh->export,
				msh->envp, remove_plus(var));
	}
	else if (tmp == 0 && ft_is_in_tab(var, msh->export, tmp) == 0)
		add_empty_var(var, msh);
	return (0);
}

int	ft_invalid_identifier(char *str)
{
	int	i;

	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			break ;
		if (ft_isalnum(str[i]) == 0 && str[0] != '_')
			return (1);
		i++;
	}
	return (0);
}
