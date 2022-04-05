/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:27:45 by ntan              #+#    #+#             */
/*   Updated: 2022/04/05 19:28:03 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*final_cmd_block(t_list *cmd, t_block *res, t_prog *msh, char *str)
{
	res->input_type = find_input_type(str);
	res->output_type = find_output_type(str);
	clean_cmd(res, str, msh);
	cmd->content = res;
	return (str);
}

void	quote_to_block(int *i, int *d_quote, int *s_quote, char *str)
{
	if (str[*i] == '"')
	{
		(*i)++;
		(*d_quote)++;
	}
	if (str[*i] == '\'')
	{
		(*i)++;
		(*s_quote)++;
	}
}