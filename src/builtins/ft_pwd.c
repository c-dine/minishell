/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:50:53 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 18:03:56 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_pwd(t_prog *msh)
{
	char	*path;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		ft_error(PATH_CORRUPTED, "pwd", 1);
		return (NULL);
	}
	path = ft_strdup(tmp);
	if (msh->double_slash == 1)
		path = ft_strjoin("/", path);
	free(tmp);
	return (path);
}

int	ft_pwd_builtin(t_prog *msh)
{
	if (ft_pwd(msh) == NULL)
		return (1);
	else
	{
		write(1, ft_strjoin(ft_pwd(msh), "\n"), ft_strlen(ft_pwd(msh)) + 1);
		return (0);
	}
}
