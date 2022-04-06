/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:27:45 by ntan              #+#    #+#             */
/*   Updated: 2022/04/06 15:49:02 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cmd_to_block_2(char *str, t_block *res, t_prog *msh, int i)
{
	int		quote[2];

	quote[0] = 0;
	quote[1] = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (str[i] == '"')
				quote[0]++;
			else if (str[i] == '\'')
				quote[1]++;
			i++;
		}
		if (quote[0] % 2 == 0 && quote[1] % 2 == 0
			&& (str[i] == '<' || str[i] == '>'))
		{
			i++;
			if (parse_duoput(res, str, &i, msh) == 1)
				return (ft_error(PARSE_ERROR, "minishell", 2), 0);
		}
		else if (str[i])
			i++;
	}
	return (1);
}

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
	else if (str[*i] == '\'')
	{
		(*i)++;
		(*s_quote)++;
	}
}