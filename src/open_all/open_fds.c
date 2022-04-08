/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:56:10 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 13:30:54 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_input(t_block *block, int *i)
{
	if (block->t_fd->tab[*i] == 1)
		block->input_fd = open_trioput_file(block->input,
				1, block->t_fd->in++);
	else if (block->t_fd->tab[*i] == 4 && block->input_type == 2)
		block->input_fd = open_heredoc_fd(block);
}

int	open_fds(t_block *block)
{
	int	tmp;
	int	i;

	i = 0;
	while (i < block->t_fd->i)
	{
		open_input(block, &i);
		if (block->input_fd == -1)
			return (-1);
		tmp = -2;
		if (block->t_fd->tab[i] == 2)
			block->output_fd = open_trioput_file(block->output, 2,
					block->t_fd->out++);
		else if (block->t_fd->tab[i] == 3)
			block->output_fd = open_trioput_file(block->outputs_append,
					3, block->t_fd->append++);
		if (block->output_type == 1)
			tmp = open_and_close(block->outputs_append, 3);
		else if (block->output_type == 2)
			tmp = open_and_close(block->output, 2);
		if (block->output_fd == -1 || tmp == -1)
			return (-1);
		i++;
	}
	return (0);
}
