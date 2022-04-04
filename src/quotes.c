/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:30:08 by cdine             #+#    #+#             */
/*   Updated: 2022/04/04 15:03:51 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_d_quote(t_index *i, t_index *quote, char *res, char *str)
{
	if (quote->i % 2 == 1)
		res[i->j++] = str[i->i++];
	else
	{
		i->i++;
		quote->j++;
	}
}

void	if_s_quote(t_index *i, t_index *quote, char *res, char *str)
{
	if (quote->j % 2 == 1)
		res[i->j++] = str[i->i++];
	else
	{
		i->i++;
		quote->i++;
	}
}

char	*ft_quotes(char *str)
{
	t_index	quote;
	t_index	i;
	char	*res;

	mempush(&res, sizeof(char), ft_strlen(str) + 1);
	i.i = 0;
	i.j = 0;
	quote.i = 0;
	quote.j = 0;
	while (str[i.i])
	{
		if (str[i.i] == '"')
			if_d_quote(&i, &quote, res, str);
		else if (str[i.i] == '\'')
			if_s_quote(&i, &quote, res, str);
		else
			res[i.j++] = str[i.i++];
	}
	res[i.j] = '\0';
	return (res);
}
