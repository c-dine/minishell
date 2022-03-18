/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:14:15 by cdine             #+#    #+#             */
/*   Updated: 2022/03/18 01:12:05 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_process_line(char *line, t_prog *minishell)
{
	printf("\033[0;37m");
	add_history(line);
	line = replace_var(line, minishell);
	if (ft_parsing(line, minishell) == -1)
		return (-1);
    // check cmds with access
    // set pipes with fds
    // fork processes avec distinction entre builtins et cmds
	return (0);
}
