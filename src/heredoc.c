/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:19:17 by ntan              #+#    #+#             */
/*   Updated: 2022/04/03 13:27:59 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_end_spaces(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while(i >= 0 && str[i] == ' ')
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
	mempush(&res, sizeof(char), ft_strlen((char *)s1) + 1 + ft_strlen((char *)s2) + 1);
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
	if (str[i] == '"' || str[i] == '\'')
	{
		str = ft_split(&str[i], '<')[0];
		str = ft_split(str, '>')[0];
	}
	else
	{
		while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != ' ')
			i++;
		mempush(&res, sizeof(char), i - marker + 1);
		ft_strlcpy(res, &str[marker], i - marker + 1);
		return (res);
	}
	str = ft_quotes(str);
	rm_end_spaces(str);
	return (str);
}

int	heredoc_prompt(t_heredoc *heredoc, char *delim, t_prog *msh)
{
	char	*buf;
	char 	*res;
	int		save_in;
	
	save_in = dup(STDIN_FILENO);
	res = "";
	while (1)
	{
		buf = readline("heredoc> ");
		if (buf == NULL)
		{
			if (error_code == 130)
			{
				dup2(save_in, STDIN_FILENO);
				close(save_in);
				return (1);
			}
			ft_error(BASH_WARNING, "warning: here-document delimited by end-of-file", 0);
			break ;
		}
		// printf("delim = |%s|\n", delim);
		if (ft_strncmp(delim, buf, ft_strlen(buf)) == 0 && ft_strlen(buf) == ft_strlen(delim))
			break;
		buf = replace_var(buf, msh);
		res = hd_strjoin(res, buf);
	}
	heredoc->str = res;
	close(save_in);
	return (0);
}

void	*print_heredoc(char *str, t_heredoc *heredoc, t_prog *msh)
{
	int i;
	char *delim;

	i = 1;
	delim = NULL;
	while (str[i])
	{
		if (str[i] == '<' && str[i - 1] == '<')
		{
			delim = find_delim(&str[i]);
			printf("%s\n", delim);
			rm_end_spaces(delim);
			if (delim == NULL)
				return (ft_error(PARSE_ERROR, "no heredoc delimiter", 2), NULL); // AAAA pas pareil mais bon
			if (heredoc_prompt(heredoc, delim, msh) == 1)
				return (NULL);
		}
		i++;
	}
	return ((void*)1);
}

// int fill_heredoc(t_heredoc *heredoc, char *str)
// {
// 	// heredoc->delim = find_delim(str);
// 	// if (heredoc->delim == NULL)
// 	// 	return (-1);
// 	// generate_random_file(&heredoc->temp, &heredoc->fd);
// 	return (1);
// }

t_heredoc *add_heredoc(t_list *cmd, t_prog *msh)
{
	t_heredoc	*heredoc;
	char		*hd_pos;/** RETOURNE LA POSITTION A PARTI DU DEUXIEME CHEVRON **/

	// printf("%s\n", (char*)cmd->content);
	mempush(&heredoc, sizeof(*heredoc), 1);
	heredoc->fd = -1;
	hd_pos = find_heredoc((char*)cmd->content);
	if (hd_pos == NULL)
		return (heredoc);
	if (print_heredoc((char*)cmd->content, heredoc, msh) == NULL)
		return (NULL);
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
		signal(SIGINT, signal_heredoc);
		temp2->next = hd_lstnew(add_heredoc(temp, msh));
		sigaction(SIGINT, &msh->sa, NULL);
		if (temp2->next->content == NULL)
			return (NULL); //AAAAAAA define error
		temp = temp->next;
		temp2 = temp2->next;
	}
	return ((void*)1);
}
