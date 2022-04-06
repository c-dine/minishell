/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:13:38 by ntan              #+#    #+#             */
/*   Updated: 2022/04/06 13:50:20 by ntan             ###   ########.fr       */
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

char	*find_delim_2(char *str, int i, int marker, t_heredoc *heredoc)
{
	char	*res;
	char	*temp;

	while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != ' ')
		i++;
	mempush(&res, sizeof(char), i - marker + 1);
	ft_strlcpy(res, &str[marker], i - marker + 1);
	temp = ft_quotes(res);
	if (ft_strncmp(temp, res, ft_strlen(res)) != 0)
		heredoc->expand = 0;
	return (temp);
}

char	*find_delim(char *str, t_heredoc *heredoc)
{
	int		i;
	int		marker;
	char	*temp;

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
		return (find_delim_2(str, i, marker, heredoc));
	temp = ft_quotes(str);
	if (ft_strncmp(temp, str, ft_strlen(str) != 0))
		heredoc->expand = 0;
	rm_end_spaces(temp);
	return (temp);
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
