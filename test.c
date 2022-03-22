/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:58:49 by cdine             #+#    #+#             */
/*   Updated: 2022/03/22 19:32:55 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
#include "libft/libft.h"
#include <stddef.h>
#include <stdlib.h>



int main()
{
	char *name;
	int fd;
	int i;
	int max;

	max = 64;
	name = malloc(sizeof(char) * (max + 1));
	i = -1;
	while (++i < max)
		name[i] = 'a';
	name[i] = '\0';
	i = 0;
	while (1)
	{
		fd = open(name, O_CREAT | O_EXCL | O_RDWR, 0644);
		if (fd > 0)
			break ;
		if (name[i] < 'z')
			name[i]++;
		else
			i++;
		if (i > max - 1)
			i = 0;
	}
	return 0;
}
