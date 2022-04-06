/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:21 by cdine             #+#    #+#             */
/*   Updated: 2022/04/06 17:58:40 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_line_break_option(char *option)
{
	int	i;

	if (option[1] != 'n')
		return (0);
	i = 1;
	while (option[i])
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	put_line_together2(int *i, int *k, char *res, char **str)
{
	int	j;

	j = 0;
	while (str[*i][j])
		res[(*k)++] = str[*i][j++];
	(*i)++;
	if (str[*i])
		res[(*k)++] = ' ';
	else
		res[*k] = '\0';
}

char	*put_line_together(char **str)
{
	int		i;
	int		k;
	int		size_res;
	char	*res;

	size_res = 0;
	i = 0;
	while (str[i])
		size_res += ft_strlen(str[i++]) + 1;
	if (!size_res)
		return (NULL);
	mempush(&res, sizeof(char), size_res);
	i = 0;
	k = 0;
	while (str[i])
		put_line_together2(&i, &k, res, str);
	return (res);
}

void	ft_display(char *str, int n)
{
	if (str)
		write(1, str, ft_strlen(str));
	if (n == 0)
		write(1, "\n", 1);
}

int	ft_echo(char **cmd)
{
	int		i;
	int		n;
	char	*str;

	n = 0;
	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			n += is_line_break_option(cmd[i]);
			if (is_line_break_option(cmd[i]) == 0)
				break ;
			i++;
		}
		else
			break ;
	}
	str = put_line_together(&cmd[i]);
	ft_display(str, n);
	return (0);
}
