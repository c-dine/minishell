/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:49:33 by ntan              #+#    #+#             */
/*   Updated: 2022/04/04 15:50:50 by ntan             ###   ########.fr       */
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

void	print_export(char **tab)
{
	int	i;

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