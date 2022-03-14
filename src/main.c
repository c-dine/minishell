/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/14 08:18:24 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prog	minishell;

	(void)argc;
	(void)argv;
	init_prog(&minishell, envp);
	// signal_manager(&minishell);
	while (1)
	{
		printf("\033[1;33m");
		ft_process_line(readline("minishell> "), &minishell);
		// t_list	*temp;
		// temp = minishell.cmds;
		// while (temp)
		// {
		// 	printf("%s\n", temp->content->cmd);
		// 	printf("%s\n", temp->content->output);
		// 	printf("%s\n", temp->content->input);
		// 	printf("main : %s\n", (char *)temp->content);
		// 	temp = temp->next;
		// }
		// ft_lstclear(&temp, free);
	}
	// destroy(&minishell);
	memrelease();
	return (0);
}
