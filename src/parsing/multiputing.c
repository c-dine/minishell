/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiputing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:00:13 by ntan              #+#    #+#             */
/*   Updated: 2022/04/07 19:55:32 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	{
		res->input_type = 2;
		res->t_fd->tab[res->t_fd->i] = 4;
		res->t_fd->i++;
	}
}

char	*parse_duoput_2(char *str, int *i)
{
	int		marker;
	char	*temp;

	marker = *i;
	while (str[*i] && str[*i] != ' ')
	{
		(*i)++;
		if (str[*i] == '<' || str[*i] == '>')
			break ;
	}
	mempush(&temp, sizeof(char), *i - marker + 1);
	ft_strlcpy(temp, &str[marker], *i - marker + 1);
	return (temp);
}

int	parse_duoput(t_block *res, char *str, int *i, t_prog *msh)
{
	int		tmp;
	char	*temp;

	tmp = 0;
	if (str[*i - 1] == '>')
		tmp = 1;
	if (str[*i - 1] == '>' && str[*i] == '>')
	{
		(*i)++;
		tmp = 2;
	}
	if (str[*i - 1] == '<' && str[*i] == '<')
		tmp = 3;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == '|' || (str[*i] == '>' && str[*i - 1] != '>')
		|| (str[*i] == '<' && str[*i - 1] != '<') || str[*i] == '\0')
		return (1);
	temp = parse_duoput_2(str, i);
	parse_duoput_3(tmp, msh, res, temp);
	return (0);
}

int	find_output_type(char *cmd)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	while (cmd[i])
	{
		if (cmd[i] && (i >= 1 && cmd[i - 1]) && cmd [i] == '>'
			&& (i >= 1 && cmd[i - 1] == '>'))
			type = 2;
		else if (cmd[i] && cmd [i] == '>')
			type = 1;
		i++;
	}
	return (type);
}

int	find_input_type(char *cmd)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	while (cmd[i])
	{
		if (cmd[i] && (i >= 1 && cmd[i - 1])
			&& cmd [i] == '<' && (i >= 1 && cmd[i - 1] == '<'))
			type = 2;
		else if (cmd[i] && cmd [i] == '<')
			type = 1;
		i++;
	}
	return (type);
}
