/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:13:28 by cdine             #+#    #+#             */
/*   Updated: 2022/04/04 12:00:35 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_path(char *cmd, int check_type)
{
	if (cmd == NULL)
		return (-1);
	if (access(cmd, R_OK) == 0)
	{
		if (check_type == 1)
			return (1);
		else
		{
			memfree(cmd);
			return (2);
		}
	}
	else
		return (-1);
}

char	*get_absolute_path(char *cmd, char **envp)
{
	int		i;
	char	**alldir;
	char	*pathcmd;

	if (ft_get_envp(envp) == NULL)
		return (NULL);
	alldir = ft_split(ft_get_envp(envp), ':');
	i = 0;
	while (alldir[i])
	{
		pathcmd = ft_strcatcmd(alldir[i], cmd);
		if (access(pathcmd, R_OK) == 0)
			return (pathcmd);
		memfree(pathcmd);
		i++;
	}
	return (NULL);
}

int	check_is_builtin(char *cmd)
{
	if (ft_strlen(cmd) == 4 && ft_strncmp(cmd, "echo", 4) == 0)
		return (3);
	else if (ft_strlen(cmd) == 2 && ft_strncmp(cmd, "cd", 2) == 0)
		return (4);
	else if (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "pwd", 3) == 0)
		return (5);
	else if (ft_strlen(cmd) == 6 && ft_strncmp(cmd, "export", 6) == 0)
		return (6);
	else if (ft_strlen(cmd) == 5 && ft_strncmp(cmd, "unset", 5) == 0)
		return (7);
	else if (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "env", 3) == 0)
		return (8);
	else if (ft_strlen(cmd) == 4 && ft_strncmp(cmd, "exit", 4) == 0)
		return (9);
	return (-1);
}

void	ft_get_cmdname(char **cmd)
{
	int		marker;
	int		i;

	i = 0;
	marker = 0;
	while (cmd[0][i])
	{
		if (cmd[0][i] == '/')
			marker = i;
		i++;
	}
	if (cmd[0][marker] == '/')
	{
		i = 0;
		while (cmd[0][marker + 1])
		{
			cmd[0][i] = cmd[0][marker + 1];
			marker++;
			i++;
		}
		cmd[0][i] = '\0';
	}
}
