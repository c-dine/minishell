/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/07 17:35:16 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void) 	argc;
	(void) 	argv;
	t_prog	*minishell;
	int 	i;

	printf("\033[1;33m");
	minishell = init_prog(envp);
	while (1)
	{
		ft_process_line(readline("minishell> "), minishell);
		i = 0;
		while (minishell->cmd_tab[i])
			printf("%s\n",minishell->cmd_tab[i++]);
	}
	return (0);
}