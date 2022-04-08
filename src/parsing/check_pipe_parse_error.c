/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_parse_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:43:04 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 15:18:09 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	if_quotes(int *s_quote, int *d_quote, char *line, int *i)
{
	if (line[*i] == '"' && *s_quote % 2 == 0)
		(*d_quote)++;
	else if (line[*i] == '\'' && *d_quote % 2 == 0)
		(*s_quote)++;
	(*i)++;
}

void	next_if(char *line, int i, int *tmp, int *pipe)
{
	if (line[i] != ' ' && line[i] != '|')
		(*tmp)++;
	if (line[i] == '|' && *pipe == 0)
		(*pipe)++;
}

int	ft_check_pipe_parse_error(char *line)
{
	int	i;
	int	tmp;
	int	pipe;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	pipe = 0;
	tmp = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			if_quotes(&s_quote, &d_quote, line, &i);
		next_if(line, i, &tmp, &pipe);
		if (line[i] == '|' && pipe == 1 && tmp == 0
			&& s_quote % 2 == 0 && d_quote % 2 == 0)
			return (1);
		else if (line[i] == '|' && pipe == 1 && tmp != 0)
			tmp = 0;
		if (line[i])
			i++;
	}
	return (0);
}
