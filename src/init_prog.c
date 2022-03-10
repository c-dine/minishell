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

void	init_prog(t_prog *minishell, char **envp)
{
	minishell->envp = envp;
	minishell->garbage = ft_lstnew(0);
}

void	destroy(t_prog *prog)
{
	if (prog->envp)
		free(prog->envp);
	free(prog);
}