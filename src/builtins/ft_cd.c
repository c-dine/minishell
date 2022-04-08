/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:44:40 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 18:20:29 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd_home(char *cmd, t_prog *msh)
{
	if (get_var_content("$HOME", msh) == NULL)
	{
		write(STDERR_FILENO, "minishell: cd: HOME not set\n",
			ft_strlen("minishell: cd: HOME not set\n"));
		g_error_code = 1;
	}
	else if (cmd == NULL || cmd[0] == '~')
		chdir(get_var_content("$HOME", msh));
}

void	ft_cd_oldpwd(t_prog *msh)
{
	if (get_var_content("$OLDPWD", msh) == NULL)
	{
		write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n",
			ft_strlen("minishell: cd: OLDPWD not set\n"));
		g_error_code = 1;
	}
	else
		chdir(get_var_content("$OLDPWD", msh));
}

void	ft_add_oldpwd(char *cmd, t_prog *msh)
{
	char	**tmp;

	if (cmd)
	{
		tmp = NULL;
		mempush(&tmp, sizeof(char *), 3);
		tmp[0] = ft_strdup("export");
		tmp[1] = ft_strjoin("OLDPWD=", cmd);
		tmp[2] = NULL;
		ft_export(tmp, msh);
	}
}

void	ft_update_pwd(t_prog *msh)
{
	char	**tmp;
	char	*tmp2;
	char	*path;

	tmp2 = getcwd(NULL, 0);
	if (tmp2 == NULL)
		path = ft_strdup("");
	else
		path = ft_strdup(tmp2);
	free(tmp2);
	if (msh->double_slash == 1)
		path = ft_strjoin("/", path);
	tmp = NULL;
	mempush(&tmp, sizeof(char *), 3);
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strjoin("PWD=", path);
	tmp[2] = NULL;
	ft_export(tmp, msh);
}

int	ft_cd(char **cmd, t_prog *msh)
{
	DIR	*tmp;

	if (cmd[1] && cmd[2])
		return (g_error_code = 1, write(STDERR_FILENO,
				"minishell: cd: too many arguments\n",
				ft_strlen("minishell: cd: too many arguments\n")), 1);
	if (cmd[1] == NULL || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
		return (ft_cd_home(cmd[1], msh), 0);
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		return (ft_cd_oldpwd(msh), 0);
	if (access(cmd[1], F_OK) == -1)
		return (ft_error(FILE_NOT_FOUND, cmd[1], 1), 1);
	tmp = opendir(cmd[1]);
	if (!tmp)
		return (ft_error(INVALID_DIRECTORY, ft_strjoin("cd: ", cmd[1]), 1), 1);
	closedir(tmp);
	ft_add_oldpwd(ft_pwd(msh), msh);
	if (ft_strncmp(cmd[1], "//", 3) == 0)
		msh->double_slash = 1;
	else if (ft_strncmp(cmd[1], "/", 1) == 0)
		msh->double_slash = 0;
	chdir(cmd[1]);
	ft_update_pwd(msh);
	return (0);
}
