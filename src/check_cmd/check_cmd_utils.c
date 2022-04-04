/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:56:07 by cdine             #+#    #+#             */
/*   Updated: 2022/04/04 11:57:47 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	**ft_check_split_cmd(char **cmd)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	while (cmd[0][i])
	{
		if (cmd[0][i] == ' ')
			space++;
		i++;
	}
	if (space != 0)
		cmd = ft_split(cmd[0], ' ');
	return (cmd);
}
