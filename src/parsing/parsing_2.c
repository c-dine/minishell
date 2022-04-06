/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:27:45 by ntan              #+#    #+#             */
/*   Updated: 2022/04/06 18:32:47 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_block(t_block *res)
{
	mempush(&res->cmd, sizeof(char *), 1);
	mempush(&res->output, sizeof(char *), 1);
	mempush(&res->input, sizeof(char *), 1);
	mempush(&res->outputs_append, sizeof(char *), 1);
	res->cmd[0] = 0;
	res->input[0] = 0;
	res->output[0] = 0;
	res->outputs_append[0] = 0;
	res->input_fd = -2;
	res->output_fd = -2;
	res->sig_status = 0;
}

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
	// printf("|%s|\n", cmd->content->cmd[0]);
	return (str);
}
