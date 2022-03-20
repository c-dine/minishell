/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:59:02 by ntan              #+#    #+#             */
/*   Updated: 2022/03/17 23:42:57 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **add_to_duotab(char **tab, char *element)
{
	char **res;
	int i;

	res = NULL;
	i = 0;
	while (tab[i])
		i++;
	mempush(&res, sizeof(char*), i + 2);
	if (res == NULL)
		return (NULL);
	i = -1;
	while (tab[++i])
		res[i] = tab[i];
	res[i] = element;
	res[++i] = 0;
	return (res);
}

void print_duotab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("tab [%d] : %s\n", i, tab[i]);
		i++;
	}	
}

int strlen_duotab(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_nblen(int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb >= 1)
	{
		nb /= 10;
		len++;
	}
	return (len);
}