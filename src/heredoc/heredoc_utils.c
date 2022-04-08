/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:11:06 by ntan              #+#    #+#             */
/*   Updated: 2022/04/08 16:07:55 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	rm_end_spaces(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] == ' ')
	{
		str[i] = '\0';
		i--;
	}
}

char	*hd_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = NULL;
	mempush(&res, sizeof(char), ft_strlen((char *)s1)
		+ 1 + ft_strlen((char *)s2) + 1);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j++] = '\n';
	res[j++] = '\0';
	return (res);
}

void	generate_random_file(char **temp, int *hd_fd)
{
	char			*name;
	unsigned int	n;
	int				fd;

	n = 0;
	while (1)
	{
		name = ft_itoa(n);
		fd = open(name, O_CREAT | O_EXCL | O_RDWR, 0644);
		if (fd > 0)
			break ;
		n++;
	}
	*temp = name;
	*hd_fd = fd;
}

int	ctrlc_heredoc(int save_in)
{
	dup2(save_in, STDIN_FILENO);
	close(save_in);
	return (1);
}
