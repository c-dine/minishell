/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:21 by cdine             #+#    #+#             */
/*   Updated: 2022/03/10 12:38:37 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	is_line_break_option(char *option)
{
	int	i;

	i = 1;
	while (option[i])
	{
		if (option[i] != 'n')
			return (0);
	}
	return (1);
}

char *put_line_together(char **)

// input cmd -> "echo -n -n hello les copains"
void	ft_echo(char *cmd)
{
	int		i;
	int		n;
	char	**split_cmd;
	char	*str;

	split_cmd = ft_split(cmd, ' ');
	n = 0;
	i = 1;
	while (split_cmd[i])
	{
		if (split_cmd[i][0] == '-')
		{
			n = is_line_break_option(split_cmd[i]);
			if (n = 0)
				break ;
			i++;
		}
		else
			break ;
	}
	str = put_line_together(&split_cmd[i]);
	destroy_split_line();
	ft_display(str, n);
}