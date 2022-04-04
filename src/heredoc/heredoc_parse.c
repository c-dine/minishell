/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:13:38 by ntan              #+#    #+#             */
/*   Updated: 2022/04/04 14:26:03 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_heredoc(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 1)
	{
		if (str[i] == '<' && str[i - 1] == '<')
			return (ft_strdup(&str[i]));
		i--;
	}
	return (NULL);
}

char	*find_delim_2(char *str, int i, int marker)
{
	char	*res;

	while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != ' ')
		i++;
	mempush(&res, sizeof(char), i - marker + 1);
	ft_strlcpy(res, &str[marker], i - marker + 1);
	res = ft_quotes(res);
	return (res);
}

char	*find_delim(char *str)
{
	int		i;
	int		marker;

	i = 0;
	if (str[i] == '<')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|' || str[i] == '>'
		|| str[i] == '<' || str[i] == '\0')
		return (NULL);
	marker = i;
	if (str[i] == '"' || str[i] == '\'')
	{
		str = ft_split(&str[i], '<')[0];
		str = ft_split(str, '>')[0];
	}
	else
		return (find_delim_2(str, i, marker));
	str = ft_quotes(str);
	rm_end_spaces(str);
	return (str);
}

char	*hd_error(char *delim)
{
	char	*str1;
	char	*str2;
	char	*res;

	str1 = "warning: here-document delimited by end-of-file (wanted `";
	str2 = "')";
	res = ft_strjoin(str1, delim);
	res = ft_strjoin(res, str2);
	return (res);
}
