/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:13:28 by cdine             #+#    #+#             */
/*   Updated: 2022/03/20 15:19:25 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strlen(envp[i]) > 5 && envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

char	*ft_strcatcmd(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	mempush(&result, sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 2);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i++] = '/';
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

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

int	ft_findslash(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
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

void	ft_check_cmds(t_prog *msh)
{
	t_list	*temp;

	temp = msh->cmds->next;
	while (temp)
	{
		temp->content->cmd_type = check_is_builtin(temp->content->cmd[0]);
		if (temp->content->cmd_type == -1)
		{
			if (ft_findslash(temp->content->cmd[0]) == 1)
				temp->content->cmd_type = check_path(temp->content->cmd[0], 1);
			else
				temp->content->cmd_type = check_path(get_absolute_path(temp->content->cmd[0], msh->envp), 2);
		}
		printf("CMD CHECK OUTPUT : %d\n", temp->content->cmd_type);
		temp = temp->next;
	}
}