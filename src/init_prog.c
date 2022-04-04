/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 01:07:55 by ntan              #+#    #+#             */
/*   Updated: 2022/04/04 15:46:54 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_code;

void	init_export_2(char **tab, char **res)
{
	int	i;
	int	j;
	int	k;

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
}

char	**init_export(char **tab)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	while (tab[i])
		i++;
	mempush(&res, sizeof(char *), i + 1);
	init_export_2(tab, res);
	return (res);
}

void	init_prog(t_prog *minishell, char **envp, struct sigaction *sa)
{
	minishell->envp = envp;
	minishell->garbage = ft_lstnew(0);
	minishell->export = init_export(envp);
	error_code = 0;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
	sa->sa_sigaction = signal_manager;
}
