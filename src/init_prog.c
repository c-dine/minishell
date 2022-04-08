/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 01:07:55 by ntan              #+#    #+#             */
/*   Updated: 2022/04/08 15:15:01 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_error_code;

void	init_export2(int *i_res, int *i, char **res, char **tab)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	mempush(&res[*i_res], sizeof(char), ft_strlen(tab[*i]) + 3);
	while (tab[*i][j] != '=')
		res[*i_res][k++] = tab[*i][j++];
	res[*i_res][k++] = tab[*i][j++];
	res[*i_res][k++] = '"';
	while (tab[*i][j])
		res[*i_res][k++] = tab[*i][j++];
	res[*i_res][k++] = '"';
	res[*i_res][k] = '\0';
	(*i)++;
	(*i_res)++;
}

char	**init_export(char **tab)
{
	char	**res;
	int		i;
	int		i_res;

	res = NULL;
	i = 0;
	while (tab[i])
		i++;
	mempush(&res, sizeof(char *), i + 1);
	i = 0;
	i_res = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "_=", 2) == 0)
			i++;
		else
			init_export2(&i_res, &i, res, tab);
	}
	res[i_res] = NULL;
	return (res);
}

void	ft_shlvl(t_prog *msh, int add)
{
	char	**tmp;
	int		shlvl;

	shlvl = ft_atoi(get_var_content("$SHLVL", msh));
	if (add == 1)
		shlvl++;
	else if (shlvl > 0)
		shlvl--;
	tmp = NULL;
	mempush(&tmp, sizeof(char *), 3);
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strjoin("SHLVL=", ft_itoa(shlvl));
	tmp[2] = NULL;
	ft_export(tmp, msh);
}

void	init_prog(t_prog *minishell, char **envp)
{
	minishell->prev_err_code = 0;
	g_error_code = 0;
	minishell->envp = envp;
	minishell->garbage = ft_lstnew(0);
	minishell->export = init_export(envp);
	ft_shlvl(minishell, 1);
	minishell->fd_to_close_1 = -2;
	minishell->fd_to_close_2 = -2;
}
