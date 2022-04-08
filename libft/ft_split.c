/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:58:49 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 13:49:08 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "libft.h"

void	ft_count_2(const char *s, char c, int *count, int *quote)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '"')
		{
			(*quote)++;
			i++;
		}
		if (s[i])
			(*count)++;
		while (((*quote % 2 == 0 && s[i] != c) || (*quote % 2 == 1
					&& (s[i] != '"' || s[i] == '\'')) || s[i] == '"'
				|| s[i] == '\'') && s[i])
		{
			if (s[i] == '"')
				(*quote)++;
			i++;
		}
	}
}

static int	ft_count(char const *s, char c)
{
	int	count;
	int	quote;
	int s_quotes;
	int d_quotes;

	count = 0;
	quote = 0;
	s_quotes = 0;
	d_quotes = 0;
	ft_count_2(s, c, &count, &quote);
	while (*s)
	{
		if (*s == '"' || *s == '\'')
		{
			if (*s == '"' && s_quotes % 2 == 0)
				d_quotes++;
			else if (*s == '\'' && d_quotes % 2 == 0)
				s_quotes++;
		}
		s++;
	}
	if (d_quotes % 2 == 1 || s_quotes % 2 == 1)
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
	int	d_quotes;
	int	s_quotes;
	
	size = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (*s)
	{
		if (*s == '"' || *s == '\'')
		{
			if (*s == '"')
				d_quotes++;
			else if (*s == '\'')
				s_quotes++;
		}
		if (*s == c && (s_quotes % 2 == 0) && (d_quotes % 2 == 0))
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

	if (!s || ft_count(s, c) == -1)
		return (ft_error(QUOTE_NOT_CLOSED, "minishell", 2));
	mempush(&result, sizeof(char *), (ft_count(s, c) + 1));
	if (result == NULL)
		return (NULL);
	k = 0;
	i = 0;
	while (k < ft_count(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		mempush(&result[k], sizeof(char), ft_sizechain(&s[i], c) + 1);
		if (result[k] == NULL)
			return (ft_freesplit(result, k));
		ft_strlcpy(result[k++], &s[i], ft_sizechain(&s[i], c) + 1);
		i += ft_sizechain(&s[i], c);
	}
	result[ft_count(s, c)] = NULL;
	return (result);
}
