/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:58:49 by cdine             #+#    #+#             */
/*   Updated: 2022/03/30 17:33:52 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
#include "libft/libft.h"
#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*rev_char(char *str)
{
	char	*rev;
	int		i;
	int		size;

	i = 0;
	size = 0;
	size = ft_strlen(str) - 1;
	rev = malloc(sizeof(char) * (ft_strlen(str) + 1));
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


int main()
{
	 char			*name;
	 unsigned int	n;
	 int				fd;

	 while (1)
	 {
	 	name = ft_itoa(n);
	 	printf("%d\n", n);
	 	fd = open(name, O_CREAT | O_EXCL | O_RDWR, 0644);
	 	if (fd > 0)
	 		break ;
	 	n++;
	  }
	return 0;
}
