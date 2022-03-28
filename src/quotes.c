/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:30:08 by cdine             #+#    #+#             */
/*   Updated: 2022/03/28 19:00:35 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_quotes(char *str)
{
	int		s_quote;
	int		d_quote;
	int		i;
	int		j;
	char	*res;

	mempush(&res, sizeof(char), ft_strlen(str) + 1);
	i = 0;
	j = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (s_quote % 2 == 1)
				res[j++] = str[i++];
			else
			{
				i++;	
				d_quote++;
			}
		}
		else if (str[i] == '\'')
		{
			if (d_quote % 2 == 1)
				res[j++] = str[i++];
			else
			{
				i++;	
				s_quote++;
			}
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
