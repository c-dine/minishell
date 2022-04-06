/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:11:41 by cdine             #+#    #+#             */
/*   Updated: 2022/04/06 15:20:02 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_long_long(char *cmd)
{
	if (cmd[0] == '-' && (ft_strlen(cmd) > 20
			|| ft_strncmp(cmd, "-9223372036854775808", 20) > 0))
		return (1);
	else if (cmd[0] == '+' && (ft_strlen(cmd) > 20
			|| ft_strncmp(&cmd[1], "9223372036854775807", 20) > 0))
		return (1);
	else if (cmd[0] != '+' && cmd[0] != '-'
		&& (ft_strlen(cmd) > 19 || ft_strncmp(cmd,
				"9223372036854775807", 19) > 0))
		return (1);
	return (0);
}

int	ft_exit(char **cmd, t_prog *msh)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "exit\n", 5);
	if (cmd[1])
	{
		if (cmd[1][0] == '+' || cmd[1][0] == '-')
			i++;
		while (cmd[1][i])
		{
			if (ft_isdigit(cmd[1][i]) == 0)
				return (ft_error(NUMERIC_ARGUMENT, ft_strjoin("exit: ",
							cmd[1]), 2), 1);
			i++;
		}
		if (check_long_long(cmd[1]) == 1)
			g_error_code = 2;
		else
			g_error_code = ft_atoi(cmd[1]);
	}
	else
		g_error_code = msh->prev_err_code;
	if (cmd[1] && cmd[2])
		return (g_error_code = 1, 1);
	return (memrelease(), exit(g_error_code), 0);
}
