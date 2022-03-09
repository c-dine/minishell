/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 01:07:55 by ntan              #+#    #+#             */
/*   Updated: 2022/03/09 01:07:55 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_prog *init_prog()
{
	t_prog *prog;
	
	prog = malloc(sizeof(*prog));
	if (!prog)
		exit(1);
	return (prog);
}

void	destroy(t_prog *prog)
{
	int i = 0;

	printf("cmd\n");
	if (prog->cmd_tab)
	{
		while (prog->cmd_tab[i])
			free(prog->cmd_tab[i++]);
		free(prog->cmd_tab);
	}
	printf("envp\n");
	if (prog->envp)
		free(prog->envp);
	// printf("list\n");
	// if (prog->list)
	// 	free(prog->list);
	// if (prog.output_error)
	// 	free(prog.output_error);
	// free(prog);
}