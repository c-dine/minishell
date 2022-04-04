/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:24:02 by cdine             #+#    #+#             */
/*   Updated: 2022/04/04 15:25:10 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_error_file_opening(char *path_file, int option)
{
	if (option == 1)
	{
		if (access(path_file, F_OK) == -1)
			return (FILE_NOT_FOUND);
		else
			return (PERMISSION_DENIED);
	}
	else
	{
		if (access(path_file, W_OK) == -1)
			return (PERMISSION_DENIED);
		else
			return (FILE_NOT_FOUND);
	}
}


int	open_and_close(char **tab, int option)
{
	int	i;
	int	fd;

	i = 0;
	while (tab[i])
	{
		if (option == 2)
			fd = open(tab[i], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		else if (option == 3)
			fd = open(tab[i], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		if (fd == -1)
		{
			ft_error(ft_error_file_opening(tab[i], option), tab[i], 1);
			return (-1);
		}
		close(fd);
		i++;
	}
	return (0);
}
