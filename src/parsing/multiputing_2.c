/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiputing_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:37:01 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 12:37:25 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_duoput_3_if_tmp_is_3(t_block *res)
{
	res->input_type = 2;
	res->t_fd->tab[res->t_fd->i] = 4;
	res->t_fd->i++;
}

void	parse_duoput_3(int tmp, t_prog *msh, t_block *res, char *temp)
{
	if (tmp == 0)
	{
		res->input = add_to_duotab(res->input,
				ft_quotes(replace_var(temp, msh)));
		res->t_fd->tab[res->t_fd->i] = 1;
		res->t_fd->i++;
	}
	else if (tmp == 1)
	{
		res->output = add_to_duotab(res->output,
				ft_quotes(replace_var(temp, msh)));
		res->t_fd->tab[res->t_fd->i] = 2;
		res->t_fd->i++;
	}
	else if (tmp == 2)
	{
		res->outputs_append = add_to_duotab(res->outputs_append,
				ft_quotes(replace_var(temp, msh)));
		res->t_fd->tab[res->t_fd->i] = 3;
		res->t_fd->i++;
	}
	else if (tmp == 3)
		parse_duoput_3_if_tmp_is_3(res);
}
