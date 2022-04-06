/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:50:53 by cdine             #+#    #+#             */
/*   Updated: 2022/04/06 16:53:28 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_pwd(void)
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
	free(tmp);
	return (path);
}

int	ft_pwd_builtin(void)
{
	if (ft_pwd() == NULL)
		return (1);
	else
	{
		write(1, ft_strjoin(ft_pwd(), "\n"), ft_strlen(ft_pwd()) + 1);
		return (0);
	}
}
