/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:18:02 by cdine             #+#    #+#             */
/*   Updated: 2022/03/21 16:35:59 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Var doit commencer par charactere alpha
// ft_show_export sort env + rajoute tableau d'exceptions

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
	print_duotab(msh->export);
	return (0);
}

// int	add_empty_var(char *var, t_prog *msh)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	while (var[i] || var[i] == '=')
// 		i++;
// 	if (var[i] == '\0')
// 	{
// 		mempush(tmp, sizeof(char), i + 4);
// 		i = 0;
// 		while (var[i])
// 		{
// 			tmp[i] = var[i];
// 			i++;
// 		}
// 		tmp[i++] = '=';
// 	}
// 	else
// 	{
// 		mempush(tmp, sizeof(char), i + 3);
// 	}
// }

int	ft_add_to_env(char *var, t_prog *msh, int tmp)
{
	int		i;
	
	if (tmp == 1)
	{
		msh->envp = add_to_duotab(msh->envp, var);
		msh->export = add_to_duotab(msh->export, var);
	}
	else
	{
		i = 0;
		while (var[i])
		{
			if (var[i] == '=' && var[i + 1] != '\0')
			{
				msh->export = add_to_duotab(msh->export, var);
				return (0);
			}
		}
		// add_empty_var(var, msh);
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
		tmp = 0;
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '=')
				tmp = 1;
			j++;
		}
		ft_add_to_env(cmd[i], msh, tmp);
		i++;
	}
	return (0);
}