/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:55:59 by ntan              #+#    #+#             */
/*   Updated: 2021/11/30 17:50:55 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	**curr;

	curr = lst;
	while (*curr != NULL)
	{
		temp = (*curr)->next;
		del((*curr)->content);
		free(*curr);
		*curr = temp;
	}
}
