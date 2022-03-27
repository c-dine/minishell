	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 01:07:55 by ntan              #+#    #+#             */
/*   Updated: 2022/03/09 18:58:02 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int error_code;

char **init_export(char **tab)
{
	char 	**res;
	int		i;
	int		j;
	int		k;

	res = NULL;
	i = 0;
	while (tab[i])
		i++;
	mempush(&res, sizeof(char *), i + 1);
	i = 0;
	while (tab[i])
	{
		mempush(&res[i], sizeof(char), ft_strlen(tab[i]) + 3);
		j = 0;
		k = 0;
		while (tab[i][j] != '=')
			res[i][k++] = tab[i][j++];
		res[i][k++] = tab[i][j++];
		res[i][k++] = '"';
		while (tab[i][j])
			res[i][k++] = tab[i][j++];
		res[i][k++] = '"';
		res[i][k] = '\0';
		i++;
	}	
	res[i] = NULL;
	return (res);
}

void	init_prog(t_prog *minishell, char **envp)
{
	minishell->envp = envp;
	minishell->garbage = ft_lstnew(0);
	minishell->export = init_export(envp);
	error_code = 0;
}
