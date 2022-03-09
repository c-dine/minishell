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
	printf("envp\n");
	if (prog->envp)
		free(prog->envp);
	// printf("list\n");
	// if (prog->list)
	// 	free(prog->list);
	// if (prog.output_error)
	// 	free(prog.output_error);
	free(prog);
}