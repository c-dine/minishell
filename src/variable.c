/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:18:08 by cdine             #+#    #+#             */
/*   Updated: 2022/03/11 01:29:40 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



char	*replace_var(char *line, t_prog *msh)
{
	int	i;
	char	*res;

	mempush(&res, sizeof(char), get_size_with_vars())
	i = 0;
	while (line[i])
	{
		
	}
}