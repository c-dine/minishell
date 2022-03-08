/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:57:27 by marvin            #+#    #+#             */
/*   Updated: 2021/12/04 17:24:31 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_strncpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (src[i] && size--)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static int	split_string(char **res, char *str, char c, int *rank)
{
	char	*begin;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else if (str[i] != c)
		{
			begin = &str[i];
			j = 0;
			while (str[i] != c && str[i])
			{
				j++;
				i++;
			}
			res[*rank] = malloc(sizeof(char) * (j + 1));
			if (res[*rank] == NULL)
				return (0);
			ft_strncpy(res[(*rank)++], begin, j);
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		rank;

	rank = 0;
	i = 0;
	res = malloc(sizeof(char *) * (count_words((char *) s, c) + 1));
	if (res == NULL)
		return (NULL);
	if (split_string(res, (char *) s, c, &rank) == 0)
	{
		while (res[i++])
			free(res[i]);
		free(res);
		return (NULL);
	}
	res[rank] = NULL;
	return (res);
}
