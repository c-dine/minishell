/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:45:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/16 18:41:32 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int *open_trioput_file(char **tab, int option)
{
	int i;
	int j;
	int	*fd;

	mempush(&fd, sizeof(int), strlen_duotab(tab) + 1);
	j = 0;
	i = 0;
	while (tab[i])
	{
		if (option == 1) /** ICI POUR LES INPUTS **/
			fd[j] = open(tab[i], O_RDWR);
		else if (option == 2)
			fd[j] = open(tab[i], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd[j] == -1)
			return (ft_error(FILE_NOT_FOUND));
		i++;
		j++;
	}
	fd[j] = -2;
	return (fd);
}


void	init_fds(t_block *block)
{
	int *tab1 = NULL;
	int *tab2 = NULL;
	int *tab3 = NULL;

	mempush(&tab1, sizeof(int), 1);
	mempush(&tab2, sizeof(int), 1);
	mempush(&tab3, sizeof(int), 1);

	block->input_fd = tab1;
	block->output_fd = tab2;
	block->outputs_append_fds = tab3;
}

int	open_fds(t_block *block)
{
	init_fds(block);
	block->input_fd = open_trioput_file(block->input, 1);
	if (block->input_fd == NULL)
		return (-1);
	block->output_fd = open_trioput_file(block->output, 2);
	if (block->output_fd == NULL)
		return (-1);
	block->outputs_append_fds = open_trioput_file(block->outputs_append, 2);
	if (block->outputs_append_fds == NULL)
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
