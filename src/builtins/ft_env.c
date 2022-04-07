/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:31:20 by cdine             #+#    #+#             */
/*   Updated: 2022/04/07 23:05:42 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_prog *msh)
{
	char	**tmp;

	tmp = NULL;
	mempush(&tmp, sizeof(char *), 3);
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strdup("_=/usr/bin/env");
	tmp[2] = NULL;
	ft_export(tmp, msh);
	print_duotab(msh->envp);
}
