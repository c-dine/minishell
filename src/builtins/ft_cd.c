/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:44:40 by cdine             #+#    #+#             */
/*   Updated: 2022/04/05 14:47:05 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_error(PATH_CORRUPTED, "pwd", 1);
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

void	ft_special_cd(char *cmd, t_prog *msh)
{
	if (get_var_content("$HOME", msh) == NULL)
		write(STDERR_FILENO, "minishell: cd: HOME not set\n",
			ft_strlen("minishell: cd: HOME not set\n"));
	else if (cmd == NULL || cmd[0] == '~')
		chdir(get_var_content("$HOME", msh));
}

int	ft_cd(char **cmd, t_prog *msh)
{
	DIR	*tmp;

	if (cmd[2])
		return (g_error_code = 1, write(STDERR_FILENO,
				"minishell: cd: too many arguments\n",
				ft_strlen("minishell: cd: too many arguments\n")), 1);
	if (cmd[1] == NULL || ((cmd[1][0] == '~' || cmd[1][0] == '-') &&
		cmd[1][1] == '\0'))
		return (ft_special_cd(cmd[1], msh), 0);
	if (access(cmd[1], F_OK) == -1)
		return (ft_error(FILE_NOT_FOUND, cmd[1], 1), 1);
	tmp = opendir(cmd[1]);
	if (!tmp)
		return (ft_error(INVALID_DIRECTORY, ft_strjoin("cd: ", cmd[1]), 1), 1);
	closedir(tmp);
	chdir(cmd[1]);
	return (0);
}
