/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:27:45 by ntan              #+#    #+#             */
/*   Updated: 2022/04/08 13:46:08 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	chevrons_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			count++;
		i++;
	}
	return (count);
}

void	init_block(t_block *res, char *str)
{
	mempush(&res->cmd, sizeof(char *), 1);
	mempush(&res->output, sizeof(char *), 1);
	mempush(&res->input, sizeof(char *), 1);
	mempush(&res->outputs_append, sizeof(char *), 1);
	mempush(&res->cmd_path, sizeof(char), 1);
	mempush(&res->t_fd, sizeof(*res->t_fd), 1);
	mempush(&res->t_fd->tab, sizeof(int *), (chevrons_count(str) + 1));
	res->cmd_path[0] = '\0';
	res->cmd[0] = 0;
	res->input[0] = 0;
	res->output[0] = 0;
	res->outputs_append[0] = 0;
	res->input_fd = -2;
	res->output_fd = -2;
	res->t_fd->i = 0;
	res->t_fd->in = 0;
	res->t_fd->out = 0;
	res->t_fd->hd = 0;
	res->t_fd->append = 0;
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
	// int i = -1;
	// while (res->cmd[++i])
	// 	printf("%d : |%s|\n", i, res->cmd[i]);
	return (str);
}
