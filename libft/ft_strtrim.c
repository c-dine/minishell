/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:48:28 by ntan              #+#    #+#             */
/*   Updated: 2021/11/30 18:27:13 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strncpy(char *dest, char *src, int size)
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

static int	is_charset(char *charset, char c)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		end;
	int		i;
	int		msize;

	i = 0;
	end = ft_strlen((char *) s1) - 1;
	while (is_charset((char *) set, s1[end]) && s1[end])
		end--;
	while (is_charset((char *) set, s1[i]) && s1[i])
		i++;
	if (end - i < 0)
		msize = 0;
	else
		msize = end - i + 1;
	res = malloc(sizeof(char) * (msize + 1));
	if (res == NULL)
		return (NULL);
	ft_strncpy(res, (char *)&s1[i], end - i + 1);
	return (res);
}
