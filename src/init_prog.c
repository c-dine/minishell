/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 01:07:55 by ntan              #+#    #+#             */
/*   Updated: 2022/04/05 19:13:33 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_error_code;

void	init_export2(int *i, char **res, char **tab)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	mempush(&res[*i], sizeof(char), ft_strlen(tab[*i]) + 3);
	while (tab[*i][j] != '=')
		res[*i][k++] = tab[*i][j++];
	res[*i][k++] = tab[*i][j++];
	res[*i][k++] = '"';
	while (tab[*i][j])
		res[*i][k++] = tab[*i][j++];
	res[*i][k++] = '"';
	res[*i][k] = '\0';
	(*i)++;
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
	i = 0;
	while (tab[i])
		init_export2(&i, res, tab);
	res[i] = NULL;
	return (res);
}

void	init_prog(t_prog *minishell, char **envp)
{
	minishell->prev_err_code = 0;
	g_error_code = 0;
	minishell->envp = envp;
	minishell->garbage = ft_lstnew(0);
	minishell->export = init_export(envp);
	// sa->sa_flags = SA_SIGINFO;
	// sigemptyset(&sa->sa_mask);
	// sa->sa_sigaction = signal_manager;
}
