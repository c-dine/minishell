/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:45:58 by ntan              #+#    #+#             */
/*   Updated: 2021/11/30 18:27:23 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	int		temp;
	int		i;
	int		j;

	i = start;
	j = 0;
	if ((int)(ft_strlen((char *) s) - start) < 0)
		temp = 0;
	else if (ft_strlen((char *) s) - start < len)
		temp = ft_strlen((char *) s) - start;
	else
		temp = len;
	res = malloc(sizeof(char) * (temp + 1));
	if (res == NULL)
		return (NULL);
	if (start >= ft_strlen((char *) s))
	{
		res[j] = '\0';
		return (res);
	}
	while (s[i] && len--)
		res[j++] = s[i++];
	res[j] = '\0';
	return (res);
}
