/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:05:01 by ntan              #+#    #+#             */
/*   Updated: 2021/12/02 14:07:48 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	char		*begin;

	i = 0;
	if (little[0] == 0)
		return ((char *) big);
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			begin = (char *) &big[i];
			while (i < len && little[j] && big[i] && (big[i++] == little[j++]))
			{
				if (little[j] == '\0')
					return (begin);
			}
			i = i - j + 1;
		}
		else
			i++;
	}
	return (NULL);
}
