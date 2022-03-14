/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:58:49 by cdine             #+#    #+#             */
/*   Updated: 2022/03/14 18:57:05 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stddef.h>
#include <stdlib.h>

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;
	int	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		// if (s[i] == '"')
		// {
		// 	quote++;
		// 	i++;
		// }
		if (s[i])
			count++;
		while (((quote % 2 == 0 && s[i] != c) || (quote % 2 == 1 && s[i] != '"') || s[i] == '"') && s[i])
		{
			if (s[i] == '"')
				quote++;
			i++;
		}
	}
	if (quote % 2 == 1)
		return (-1);
	return (count);
}

static char	**ft_freesplit(char **result, int k)
{
	while (k >= 0)
	{
		free(result[k]);
		k--;
	}
	return (NULL);
}

static int	ft_sizechain(const char *s, char c)
{
	int	size;
	int	nb_quotes;

	size = 0;
	nb_quotes = 0;
	while (*s)
	{
		if (*s == '"')
			nb_quotes++;
		if (*s == c && (nb_quotes == 2 || nb_quotes == 0))
			break ;
		size++;
		s++;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		k;

	// renvoyer erreur de comportement non defini quand renvoie NULL -> quand quote ouverte
	if (!s || ft_count(s, c) == -1)
		return (NULL);
	// result = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	mempush(&result, sizeof(char *), (ft_count(s, c) + 1));
	if (result == NULL)
		return (NULL);
	k = 0;
	i = 0;
	while (k < ft_count(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		// result[k] = malloc(sizeof(char) * (ft_sizechain(&s[i], c) + 1));
		mempush(&result[k], sizeof(char), ft_sizechain(&s[i], c) + 1);
		if (result[k] == NULL)
			return (ft_freesplit(result, k));
		ft_strlcpy(result[k++], &s[i], ft_sizechain(&s[i], c) + 1);
		i += ft_sizechain(&s[i], c);
	}
	result[ft_count(s, c)] = NULL;
	// i = -1;
	// while (result[++i])
	// 	printf("%s, %d\n", result[i], i);
	return (result);
}


#include <stdio.h>

int	main()
{
	char	str[100] = "salut \"echo\" \"saluuuuutt\"";
	char	**split_line;
	int		i;

	printf("%s\n", str);
	split_line = ft_split(str, ' ');
	i = 0;
	while (split_line[i])
	{
		printf("%d: %s\n", i, split_line[i]);
		i++;
	}
	return 0;
}