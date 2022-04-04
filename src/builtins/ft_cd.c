/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:44:40 by cdine             #+#    #+#             */
/*   Updated: 2022/04/04 15:38:46 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_error(PATH_CORRUPTED, "pwd", 1);
		return (1);
	}
	printf("%s\n", path);
	return (0);
}

int	ft_cd(char **cmd)
{
	DIR	*tmp;
	int	i;

	if (!cmd[1])
		return (1);
	i = 1;
	while (cmd[++i])
	{
		cmd[1] = ft_strjoin(cmd[1], " ");
		cmd[1] = ft_strjoin(cmd[1], cmd[i]);
	}
	if (access(cmd[1], F_OK) == -1)
	{
		ft_error(FILE_NOT_FOUND, cmd[1], 1);
		return (1);
	}
	tmp = opendir(cmd[1]);
	if (!tmp)
	{
		ft_error(INVALID_DIRECTORY, ft_strjoin("cd: ", cmd[1]), 1);
		return (1);
	}
	closedir(tmp);
	chdir(cmd[1]);
	return (0);
}
