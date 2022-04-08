/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:28:27 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 13:29:19 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_check_plus_equal(char **cmd, int i, int *tmp)
{
	int	j;

	j = 0;
	while (cmd[i][j])
	{
		if (cmd[i][j] == '+' && cmd[i][j + 1] == '=')
			*tmp = 2;
		if (cmd[i][j] != '+' && cmd[i][j + 1] == '=')
			*tmp = 1;
		j++;
	}
}

int	ft_export_2(char **cmd, int i, t_prog *msh)
{
	int	tmp;
	int	ret;

	ret = 0;
	while (cmd[i])
	{
		if (ft_invalid_identifier(cmd[i]) == 1)
		{
			ft_error(INVALID_IDENTIFIER, ft_strjoin("export: `", cmd[i]), 1);
			ret = 1;
			i++;
			continue ;
		}
		tmp = 0;
		ft_check_plus_equal(cmd, i, &tmp);
		ft_add_to_env(cmd[i], msh, tmp);
		i++;
	}
	return (ret);
}

int	ft_export(char **cmd, t_prog *msh)
{
	int	i;

	if (cmd[1] == NULL)
	{
		ft_show_export(msh);
		return (0);
	}
	i = 1;
	return (ft_export_2(cmd, i, msh));
}
