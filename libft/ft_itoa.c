/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:29:04 by ntan              #+#    #+#             */
/*   Updated: 2022/04/07 21:20:40 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*rev_char(char *str)
{
	char	*rev;
	int		i;
	int		size;

	i = 0;
	size = 0;
	size = ft_strlen(str) - 1;
	mempush(&rev, sizeof(char), ft_strlen(str) + 1);
	if (rev == NULL)
		return (NULL);
	while (str[i])
	{
		rev[i] = str[size - i];
		i++;
	}
	rev[i] = '\0';
	return (rev);
}

char	*ft_itoa(int n)
{
	char			res[200];
	unsigned int	quotient;
	int				reste;
	int				i;

	i = 0;
	if (n < 0)
		quotient = -n;
	else
		quotient = n;
	while (1)
	{
		reste = quotient % 10;
		quotient = quotient / 10;
		res[i++] = (reste + '0');
		if (quotient == 0)
		{
			if (n < 0)
				res[i++] = '-';
			res[i] = '\0';
			break ;
		}
	}
	return (rev_char(res));
}
