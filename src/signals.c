/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 07:50:50 by ntan              #+#    #+#             */
/*   Updated: 2022/03/14 08:18:19 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void signal_handler(int sig)
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