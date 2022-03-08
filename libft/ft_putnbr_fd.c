/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:15:11 by ntan              #+#    #+#             */
/*   Updated: 2022/02/09 17:19:27 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_putnbr_fd(int n, int fd)
// {
// 	unsigned int	n2;

// 	if (n < 0)
// 	{
// 		ft_putchar_fd('-', fd);
// 		n2 = -n;
// 	}
// 	else
// 		n2 = n;
// 	if (n2 > 9)
// 		ft_putnbr_fd(n2 / 10, fd);
// 	ft_putchar_fd(n2 % 10 + '0', fd);
// }	

void	ft_putnbr_fd(int n, int fd)
{
	char			res[200];
	unsigned int	quotient;
	unsigned int	reste;
	int				i;

	i = 0;
	if (n < 0)
		quotient = -n;
	else
		quotient = n;
	while (quotient != 0)
	{
		reste = quotient % 10;
		quotient = quotient / 10;
		res[i++] = reste + '0';
	}
	if (n < 0)
		res[i++] = '-';
	if (n == 0)
		res[i++] = '0';
	while (i-- > 0)
		write(fd, &res[i], 1);
}
