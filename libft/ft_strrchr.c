/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:03:33 by ntan              #+#    #+#             */
/*   Updated: 2021/12/02 14:07:29 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	char	*str;
	size_t	i;

	res = 0;
	i = 0;
	str = (char *) s;
	while (i <= ft_strlen(str))
	{
		if ((unsigned char) str[i] == (unsigned char) c)
			res = &str[i];
		i++;
	}
	return (res);
}
