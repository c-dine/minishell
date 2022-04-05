/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:11:41 by cdine             #+#    #+#             */
/*   Updated: 2022/04/05 19:15:50 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(char **cmd, t_prog *msh)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "exit\n", 5);
	if (cmd[1] && cmd[2])
		return (g_error_code = 1, 1);
	if (cmd[1])
	{
		while (cmd[1][i])
		{
			if (ft_isdigit(cmd[1][i]) == 0)
				return (ft_error(NUMERIC_ARGUMENT, ft_strjoin("exit: ",
							cmd[1]), 2), 1);
			i++;
		}
		g_error_code = ft_atoi(cmd[1]);
	}
	else
		g_error_code = msh->prev_err_code;
	return (0);
}
