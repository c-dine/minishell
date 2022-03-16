/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:45:26 by ntan              #+#    #+#             */
/*   Updated: 2022/03/16 16:05:07 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int open_trioput_file(char **tab, int *fd, int option)
{
	int i;
	int j;

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
			printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAH\n");
		printf("fd : %d\n", fd[j]); /********AAAAAAAAAAAAA******/
		i++;
		j++;
	}
	fd[j] = -1;
	return (0);
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
	open_trioput_file(block->input, block->input_fd, 1);
	open_trioput_file(block->output, block->output_fd, 2);
	open_trioput_file(block->outputs_append, block->outputs_append_fds, 2);

	/**TESTS**/
	print_duotab(block->input);
	print_duotab(block->output);
	print_duotab(block->outputs_append);
	/***/
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
