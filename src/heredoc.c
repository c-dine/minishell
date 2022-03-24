/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:19:17 by ntan              #+#    #+#             */
/*   Updated: 2022/03/24 16:17:12 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_prompt(t_heredoc *heredoc)
{
	char *buf;
	char *res;
	
	res = "";
	while (1)
	{
		buf = readline(">");
		printf("%s, %s\n", heredoc->delim, buf);
		if (ft_strncmp(heredoc->delim, buf, ft_strlen(heredoc->delim)) == 0)
			break;
		res = ft_strjoin(res, buf);
	}
	heredoc->str = res;
}

void	generate_random_file(char **temp, int *hd_fd)
{
	char			*name;
	unsigned int	n;
	int				fd;

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

int fill_heredoc(t_heredoc *heredoc, char *str)
{
	heredoc->delim = find_delim(str);
	if (heredoc->delim == NULL)
		return (-1);
	// generate_random_file(&heredoc->temp, &heredoc->fd);
	return (1);
}

t_heredoc *add_heredoc(t_list *cmd)
{
	t_heredoc	*heredoc;
	char		*hd_pos;/** RETOURNE LA POSITTION A PARTI DU DEUXIEME CHEVRON **/

	mempush(&heredoc, sizeof(*heredoc), 2);
	heredoc->fd = -1;
	hd_pos = find_heredoc((char*)cmd->content);
	if (hd_pos == NULL)
		return (heredoc);
	else
	{
		if (fill_heredoc(heredoc, hd_pos) == -1)
			return (NULL);
		heredoc_prompt(heredoc);
	}
	return (heredoc);
}

void *ft_heredoc(t_prog *msh)
{
	t_hd_list	*hd_list;
	t_hd_list	*temp2;
	t_list		*temp;

	temp = msh->cmds->next;
	temp2 = hd_lstnew(NULL);
	hd_list = temp2;
	while (temp)
	{
		temp2->content = add_heredoc(temp);
		if (temp2->content == NULL)
			return (NULL); //AAAAAAA define error
		temp = temp->next;
		temp2 = temp2->next;
	}
	return (hd_list);
}
