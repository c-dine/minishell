/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:32:26 by cdine             #+#    #+#             */
/*   Updated: 2022/04/09 21:13:54 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_err_status(int code, char *str, char *indic, int indic_type)
{
	if (indic_type != CMD_NOT_FOUND && indic_type != QUOTE_NOT_CLOSED
		&& ft_strncmp(indic, "minishell", 10) != 0)
		write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	if (indic)
		write(STDERR_FILENO, indic, ft_strlen(indic));
	if (indic_type == INVALID_IDENTIFIER)
		write(STDERR_FILENO, "\': ", ft_strlen("\': "));
	else
		write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	g_error_code = code;
}

void	ft_error2(int code, char *indic, int err_code)
{
	if (code == FORK_ERROR)
		set_err_status(err_code, "error", indic, code);
	else if (code == TOO_MANY_FDS)
		set_err_status(err_code, "Too many open files", indic, code);
	else if (code == BASH_WARNING)
		set_err_status(err_code, "", indic, code);
	else if (code == FILENAME_REQUIRED)
		set_err_status(err_code, "filename argument required", indic, code);
	else if (code == NUMERIC_ARGUMENT)
		set_err_status(err_code, "numeric argument required", indic, code);
	else if (code == IS_A_DIRECTORY)
		set_err_status(err_code, "Is a directory", indic, code);
	else if (code == NOT_A_DIRECTORY)
		set_err_status(err_code, "Not a directory", indic, code);
}

void	*ft_error(int code, char *indic, int err_code)
{
	if (code == CMD_NOT_FOUND)
		set_err_status(err_code, "command not found (RTFM)", indic, code);
	else if (code == FILE_NOT_FOUND)
		set_err_status(err_code, "No such file or directory", indic, code);
	else if (code == QUOTE_NOT_CLOSED)
		set_err_status(err_code, "quote not closed", indic, code);
	else if (code == PARSE_ERROR)
		set_err_status(err_code, "syntax error near unexpected token",
			indic, code);
	else if (code == PERMISSION_DENIED)
		set_err_status(err_code, "Permission denied", indic, code);
	else if (code == INVALID_IDENTIFIER)
		set_err_status(err_code, "not a valid identifier", indic, code);
	else if (code == INVALID_DIRECTORY)
		set_err_status(err_code, "Not a directory", indic, code);
	else if (code == PATH_CORRUPTED)
		set_err_status(err_code, "path corrupted", indic, code);
	ft_error2(code, indic, err_code);
	return (NULL);
}

int	return_value_file_or_folder(char *tmp2, t_list *cmd)
{
	DIR		*dir;

	dir = NULL;
	if (tmp2)
		dir = opendir(tmp2);
	else
		return (closedir(dir), ft_error(FILE_NOT_FOUND,
				cmd->content->cmd_path, 127), 127);
	if (dir == NULL)
		return (ft_error(NOT_A_DIRECTORY, cmd->content->cmd_path, 126), 126);
	else
		return (closedir(dir), ft_error(FILE_NOT_FOUND,
				cmd->content->cmd_path, 127), 127);
}

int	ft_not_file_or_folder_error(t_list *cmd)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp2 = NULL;
	tmp = ft_strdup(cmd->content->cmd_path);
	i = 1;
	while (cmd->content->cmd_path[++i])
	{
		if (cmd->content->cmd_path[i] == '/')
		{
			tmp[i] = '\0';
			if (access(tmp, F_OK) == -1)
				break ;
			tmp2 = tmp;
			tmp = ft_strdup(cmd->content->cmd_path);
		}
	}
	return (return_value_file_or_folder(tmp2, cmd));
}
