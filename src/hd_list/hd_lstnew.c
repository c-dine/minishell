/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:49:59 by ntan              #+#    #+#             */
/*   Updated: 2022/03/10 18:3902:02 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hd_list	*hd_lstnew(void *content)
{
	t_hd_list	*new;

	new = NULL;
	mempush(&new, sizeof(*new), 1);
	new->content = content;
	new->next = NULL;
	return (new);
}
