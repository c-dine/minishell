/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:54:35 by ntan              #+#    #+#             */
/*   Updated: 2022/04/06 16:57:16 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*copy_no_quotes(char *str, int size)
{
	char	*res;
	int		j;
	int		i;

	mempush(&res, sizeof(char), (size + 1));
	i = 0;
	j = 0;
	while (i < size)
	{
		if (str[i] != '\0')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*remove_quotes(char *str)
{
	int	i;
	int	size;

	size = ft_strlen(str);
	i = 0;
	if (str[0] == '\"')
	{
		while (i < size)
		{
			if (str[i] && str[i] == '\"')
				str[i] = '\0';
			i++;
		}
	}
	else
	{
		while (i < size)
		{
			if (str[i] && str[i] == '\'')
				str[i] = '\0';
			i++;
		}
	}
	return (copy_no_quotes(str, size));
}

char	**remove_empty_cmd(char **tab, int n)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	mempush(&res, sizeof(char *), n);
	while (tab[i])
	{
		if (tab[i][0] != '\0')
		{
			mempush(&res[j], sizeof(char), ft_strlen(tab[i]) + 1);
			ft_strlcpy(res[j], tab[i], ft_strlen(tab[i]) + 1);
			j++;
		}
		i++;
	}
	res[j] = 0;
	return (res);
}
