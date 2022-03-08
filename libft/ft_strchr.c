/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:09:25 by ntan              #+#    #+#             */
/*   Updated: 2021/11/30 18:25:55 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*res;
	char	*str;
	size_t	i;

	i = 0;
	res = 0;
	str = (char *) s;
	while (i <= ft_strlen(str))
	{
		if ((unsigned char) str[i] == (unsigned char) c)
		{
			res = &str[i];
			return (res);
		}
		i++;
	}
	return (res);
}
