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

void	init_prog(t_prog *minishell, char **envp)
{
	minishell->dup_fd_stdout = dup(STDOUT_FILENO);
	minishell->envp = envp;
	minishell->garbage = ft_lstnew(0);
	minishell->export = copy_duotab(envp);
	error_code = 0;
}
