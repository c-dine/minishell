/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:18:02 by cdine             #+#    #+#             */
/*   Updated: 2022/03/27 20:11:01 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_in_tab(char *var, char **tab, int tmp)
{
	int	size_var_name;
	int	i;

	if (tmp == 0)
		var = ft_strjoin(var, "=");
	size_var_name = 0;
	while (var[size_var_name] && var[size_var_name] != '=')
		size_var_name++;
	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], var, size_var_name + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_sort(char **tab)
{
	int	i;
	
	i = 0;
	while (tab[i + 1])
	{
		if (ft_strncmp(tab[i], tab[i + 1], 1000) > 0)
			return (1);
		i++;
	}
	return (0);
}

void print_export(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("declare -x ");
		printf("%s\n", tab[i]);
		i++;
	}	
}

int	ft_show_export(t_prog *msh)
{
	char	*tmp;
	int		i;

	while (ft_is_sort(msh->export) == 1)
	{
		i = 0;
		while (msh->export[i + 1])
		{
			if (ft_strncmp(msh->export[i], msh->export[i + 1], 1000) > 0)
			{
				tmp = msh->export[i];
				msh->export[i] = msh->export[i + 1];
				msh->export[i + 1] = tmp;
			}
			i++;
		}
	}
	print_export(msh->export);
	return (0);
}

int	add_empty_var(char *var, t_prog *msh)
{
	char	*tmp;
	int		i;

	i = 0;
	while (var[i] || var[i] == '=')
		i++;
	if (var[i] == '\0')
		mempush(&tmp, sizeof(char), i + 4);
	else
		mempush(&tmp, sizeof(char), i + 3);
	i = 0;
	while (var[i] != '=' && var[i])
	{
		tmp[i] = var[i];
		i++;
	}
	tmp[i++] = '=';
	tmp[i++] = '"';
	tmp[i++] = '"';
	tmp[i++] = '\0';
	msh->export = add_to_duotab(msh->export, tmp);
	return (0);
}

char	**add_to_env_tab(char **tab, char *var, int tmp)
{
	int i;
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

char *ft_unquote(char *var)
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
	int i;
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

char **cat_to_export_tab(char **export, char **envp, char *var)
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
		msh->envp = add_to_env_tab(msh->envp, ft_unquote(var), tmp);
		msh->export = add_to_env_tab(msh->export, ft_quote(var), tmp);
	}
	else if (tmp == 2)
	{
		msh->envp = cat_to_env_tab(msh->envp, ft_unquote(remove_plus(var)), tmp);
		msh->export = cat_to_export_tab(msh->export, msh->envp, remove_plus(var));
	}
	else if (tmp == 0 && ft_is_in_tab(var, msh->export, tmp) == 0)
		add_empty_var(var, msh);
	return (0);
}

int	ft_invalid_identifier(char *str)
{
	int	i;

	if (ft_isalpha(str[0]) == 0)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			break ;
		if (ft_isalnum(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(char **cmd, t_prog *msh)
{
	int	i;
	int	j;
	int	tmp;
	
	if (cmd[1] == NULL)
	{
		ft_show_export(msh);
		return (0);
	}
	i = 1;
	while (cmd[i])
	{
		if (ft_invalid_identifier(cmd[i]) == 1)
		{
			ft_error(INVALID_IDENTIFIER, ft_strjoin("export: `", cmd[i]), 1);
			i++;
			continue ;
		}
		tmp = 0;
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '+' && cmd[i][j + 1] == '=')
				tmp = 2;
			if (cmd[i][j] != '+' && cmd[i][j + 1] == '=')
				tmp = 1;
			j++;
		}
		ft_add_to_env(cmd[i], msh, tmp);
		i++;
	}
	return (0);
}