/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:58:53 by ntan              #+#    #+#             */
/*   Updated: 2022/03/10 15:00:12 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** exemple : my_alloc(listofmalloc, 10, sizeof(char)) **/
void	my_alloc(t_list *list, int size, int memsize)
{
	void *res;
	
	res = malloc(memsize * size);
	if (res == NULL)
	{
		ft_lstclear(&list, free);
		exit (1);
	}
	ft_lstadd_back(&list, ft_lstnew(&res));
}
