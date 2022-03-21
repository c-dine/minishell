/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 07:50:50 by ntan              #+#    #+#             */
/*   Updated: 2022/03/21 14:32:02 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

voidhandler(int sig)
{
	(void)sig;
	memrelease();
	printf("CTRL + C PRESSED\n");
	// exit(0)
}

void signal_manager(t_prog *msh)
{
	(void)msh;
	signal(SIGINT, signal_handler);
}