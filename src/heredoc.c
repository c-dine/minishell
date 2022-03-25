/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:19:17 by ntan              #+#    #+#             */
/*   Updated: 2022/03/25 18:36:06 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*hd_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = NULL;
	mempush(&res, sizeof(char), ft_strlen((char *)s1) + 1 + ft_strlen((char *)s2) + 1);
	if (res == NULL)
		return (NULL);
	while (s1[i])
		res[j++] = s1[i++];
	res[j++] = '\n'; 
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
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

char *find_heredoc(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (i >= 1)
	{
		if (str[i] == '<' && str[i - 1] == '<')
			return (ft_strdup(&str[i]));
		i--;
	}
	return (NULL);
}

char *find_delim(char *str)
{
	int		i;
	int		marker;
	char	*res;

	i = 0;
	if (str[i] == '<')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|' || str[i] == '>'
		|| str[i] == '<' || str[i] == '\0')
		return (NULL);
	marker = i;
	while (str[i] != '\0' && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != ' ')
		i++;
	mempush(&res, sizeof(char), i - marker + 1);
	ft_strlcpy(res, &str[marker], i - marker + 1);
	return (res);
}

void	heredoc_prompt(t_heredoc *heredoc, char *delim)
{
	char *buf;
	char *res;
	
	res = "";
	while (1)
	{
		buf = readline("heredoc>");
		if (ft_strncmp(delim, buf, ft_strlen(delim)) == 0)
			break;
		res = hd_strjoin(res, buf);
		free(buf);
	}
	heredoc->str = res;
}

void	print_heredoc(char *str, t_heredoc *heredoc)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '<' && str[i - 1] == '<')
		{
			// printf("%s\n", &str[i]);
			heredoc_prompt(heredoc, find_delim(&str[i]));
		}
		i++;
	}	
}

// int fill_heredoc(t_heredoc *heredoc, char *str)
// {
// 	// heredoc->delim = find_delim(str);
// 	// if (heredoc->delim == NULL)
// 	// 	return (-1);
// 	// generate_random_file(&heredoc->temp, &heredoc->fd);
// 	return (1);
// }

t_heredoc *add_heredoc(t_list *cmd)
{
	t_heredoc	*heredoc;
	char		*hd_pos;/** RETOURNE LA POSITTION A PARTI DU DEUXIEME CHEVRON **/

	mempush(&heredoc, sizeof(*heredoc), 1);
	heredoc->fd = -1;
	hd_pos = find_heredoc((char*)cmd->content);
	if (hd_pos == NULL)
		return (heredoc);
	print_heredoc((char*)cmd->content, heredoc);
	// else
	// {
	// 	if (fill_heredoc(heredoc, hd_pos) == -1)
	// 		return (NULL);
	// }
	return (heredoc);
}

void *ft_heredoc(t_prog *msh)
{
	t_hd_list	*temp2;
	t_list		*temp;

	temp = msh->cmds->next;
	temp2 = hd_lstnew(NULL);
	msh->heredocs = temp2;
	while (temp)
	{
		temp2->next = hd_lstnew(add_heredoc(temp));
		if (temp2->next->content == NULL)
			return (NULL); //AAAAAAA define error
		temp = temp->next;
		temp2 = temp2->next;
	}
	return ((void*)1);
}
