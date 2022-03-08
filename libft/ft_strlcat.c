/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:49:29 by ntan              #+#    #+#             */
/*   Updated: 2021/11/30 18:26:23 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = 0;
	res = (ft_strlen(dst) + ft_strlen((char *) src));
	if (size > ft_strlen(dst))
	{
		while (dst[i] && --size)
			i++;
		while (src[j] && --size)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
		return (res);
	}
	return (ft_strlen((char *)src) + size);
}
