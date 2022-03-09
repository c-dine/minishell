/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/09 18:58:32 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	*minishell;
	t_list	*temp;

	(void)argc;
	(void)argv;
	printf("\033[1;33m");
	minishell = init_prog(envp);
	// while (1)
	// {
		ft_process_line(readline("minishell> "), minishell);
		temp = minishell->list;
		while (minishell->list)
		{
			printf("%s\n",minishell->list->content);
			minishell->list = minishell->list->next;
		}
		ft_lstclear(&temp, free);
	// }
	destroy(minishell);
	return (0);
}
