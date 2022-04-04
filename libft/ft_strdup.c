/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:53:53 by ntan              #+#    #+#             */
/*   Updated: 2022/04/04 16:23:20 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	int		size_src;
	char	*src_copy;

	size_src = ft_strlen((char *)s);
	src_copy = NULL;
	mempush(&src_copy, sizeof(char), size_src + 1);
	if (src_copy == NULL)
		return (NULL);
	ft_strcpy(src_copy, (char *) s);
	return (src_copy);
}
