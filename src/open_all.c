/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:45:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/23 14:51:35 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error_file_opening(char *path_file, int option)
{
	// INPUT
	if (option == 1)
	{
		if (access(path_file, F_OK) == -1)
			return (FILE_NOT_FOUND);
		else
			return (PERMISSION_DENIED);
	}
	// OUTPUT
	else
	{
		if (access(path_file, W_OK) == -1)
			return (PERMISSION_DENIED);
		else
			return (FILE_NOT_FOUND);
	}
}

int	open_trioput_file(char **tab, int option)
{
	int i;
	int	fd;

	fd = -2;
	i = 0;
	while (tab[i])
	{
		if (option == 1) /** ICI POUR LES INPUTS **/
			fd = open(tab[i], O_RDWR);
		else if (option == 2) /** OUTPUT **/
			fd = open(tab[i], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		else if (option == 3) /** APPEND **/
			fd = open(tab[i], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		if (fd == -1)
		{
			ft_error(ft_error_file_opening(tab[i], option));
			return (-1);
		}
		if (tab[i + 1] != NULL)
			close(fd);
		i++;
	}
	return (fd);
}

int	open_and_close(char **tab, int option)
{
	int i;
	int	fd;

	i = 0;
	while (tab[i])
	{
		if (option == 2) /** OUTPUT **/
			fd = open(tab[i], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		else if (option == 3) /** APPEND **/
			fd = open(tab[i], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		if (fd == -1)
		{
			ft_error(ft_error_file_opening(tab[i], option));
			return (-1);
		}
		close(fd);
		i++;
	}
	return (0);
}

int	open_fds(t_block *block)
{
	int	tmp;

	tmp = -2;
	block->input_fd = open_trioput_file(block->input, 1);
	if (block->input_fd == -1)
		return (-1);
	if (block->output_type == 1)
		block->output_fd = open_trioput_file(block->output, 2);
	else if (block->output_type == 2)
		block->output_fd = open_trioput_file(block->outputs_append, 3);
	if (block->output_type == 1)
		tmp = open_and_close(block->outputs_append, 3);	
	else if (block->output_type == 2)
		tmp = open_and_close(block->output, 2);
	if (block->output_fd == -1 || tmp == -1)
		return (-1);
	return (0);
}

int	open_pipes(t_block *block)
{
	int	*fd;

	fd = NULL;
	mempush(&fd, sizeof(int), 2);
	pipe(fd);
	block->pipe = fd;
	return (0);
}
