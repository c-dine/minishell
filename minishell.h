/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:42 by ntan              #+#    #+#             */
/*   Updated: 2022/04/06 16:52:24 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft/libft.h"
# include <dirent.h>
# include <sys/wait.h>

# define CMD_NOT_FOUND 0
# define FILE_NOT_FOUND 1
# define QUOTE_NOT_CLOSED 2
# define PARSE_ERROR 3
# define PERMISSION_DENIED 4
# define INVALID_IDENTIFIER 5
# define INVALID_DIRECTORY 6
# define PATH_CORRUPTED 7
# define FORK_ERROR 8
# define TOO_MANY_FDS 9
# define BASH_WARNING 10
# define FILENAME_REQUIRED 11
# define NUMERIC_ARGUMENT 12

extern int	g_error_code;

typedef struct	s_prog
{
	char 				**envp;
	char				**export;
	t_list				*cmds;
	t_list				*garbage;
	t_hd_list			*heredocs;
	int					prev_err_code;
	struct sigaction	sa;
}				t_prog;

typedef struct s_index
{
	int	i;
	int	j;
}				t_index;

/** FONCTION DEMMARAGE ET FIN**/
void		init_prog(t_prog *minishell, char **envp);
void		close_all_pipes(t_list *beg_all_pipes);
void		close_trioput_fd(t_list *cmd);
void		close_main_process(t_list *node, int builtin);

/** FONCTIONS DE PARSING **/
int			ft_parsing(char *line, t_prog *minishell);
char		*replace_var(char *line, t_prog *msh);
void		ft_check_cmds(t_prog *msh);
char		*remove_quotes(char *str);
void		clean_cmd(t_block *res, char *str, t_prog *msh);
int			parse_duoput(t_block *res, char *str, int *i, t_prog *msh);
void		init_block(t_block *res);
int			find_output_type(char *cmd);
int			find_input_type(char *cmd);
char		*final_cmd_block(t_list *cmd, t_block *res, t_prog *msh, char *str);
void		quote_to_block(int *i, int *d_quote, int *s_quote, char *str);
int			cmd_to_block_2(char *str, t_block *res, t_prog *msh, int i);

/** LES SIGNAUX **/
void		signal_manager(int sig);
void		signal_heredoc(int sig);
void		signal_bs(int sig);
void		signal_fork(int sig);

/** OPENS FUNCTIONS **/
int			open_fds(t_block *block);
int			open_pipes(t_block *block);
int			open_trioput_file(char **tab, int option);
int			open_heredoc_fd(t_block *block);
int			ft_error_file_opening(char *path_file, int option);
int			open_and_close(char **tab, int option);

/** VARIABLE EXPANSION **/
char		*get_var_content(char *line, t_prog *msh);
char		*replace_var(char *line, t_prog *msh);
int			get_size_with_vars(char *line, t_prog *msh);
int			get_size_var(char *line, t_prog *msh);
char		*get_var_content(char *line, t_prog *msh);
int			check_single_quote(char *line);
void		alias_expansion(char *line, char *res, t_prog *msh);

/** CHECK CMD **/
void		ft_check_cmds(t_prog *msh);
int			check_path(char *cmd, int check_type);
char		*get_absolute_path(char *cmd, char **envp);
int			check_is_builtin(char *cmd);
void		ft_get_cmdname(char **cmd);
char		*ft_get_envp(char **envp);
char		*ft_strcatcmd(char *s1, char *s2);
int			ft_findslash(char *s);
char		**ft_check_split_cmd(char **cmd);

/** PROCESS **/
int			fork_process(t_list *cmd, t_list *beginning, t_prog *msh);
int			wait_children(t_prog *msh);
void		ft_close_builtin(int fd_out, t_list *cmd);
void		no_cmd(t_list *cmd);
int			ft_check_specialchar(char *line);
int			ft_process_line(char *line, t_prog *minishell);
void		dup_pipes(t_list *cmd, t_list *beginning);
int			cmd_pb(t_list *cmd, t_list *beginning);
int			permission_denied(t_list *cmd, t_list *beginning);


/** Fonctions utiles **/
char		**add_to_duotab(char **tab, char *element);
void		print_duotab(char **tab);
int			strlen_duotab(char **str);
char		**copy_duotab(char **tab);
int			get_fd(int *fd_tab);
int			ft_nblen(int nb);
char		*get_absolute_path(char *cmd, char **envp);
t_hd_list	*hd_lstnew(void *content);
char		*ft_quotes(char *str);

/** ERRORS **/
void		*ft_error(int code, char *indic, int err_code);
int			ft_error_file_opening(char *path_file, int option);

/** Builtin **/
int			ft_echo(char **cmd);
int			ft_export(char **cmd, t_prog *msh);
char		**add_to_env_tab(char **tab, char *var, int tmp);
char		*ft_unquote(char *var);
char		*ft_quote(char *var);
char		*remove_plus(char *var);
char		**cat_to_env_tab(char **tab, char *var, int tmp);
int			ft_is_in_tab(char *var, char **tab, int tmp);
int			ft_is_sort(char **tab);
void		print_export(char **tab);
int			ft_show_export(t_prog *msh);
int			add_empty_var(char *var, t_prog *msh);
int			ft_unset(char **cmd, t_prog *msh);
int			ft_cd(char **cmd, t_prog *msh);
char		*ft_pwd(void);
int			ft_exit(char **cmd, t_prog *msh);
int			ft_fork_builtins(t_list *cmd, t_prog *msh);
int			ft_builtin(t_list *cmd, t_prog *msh);
int			ft_pwd_builtin(void);

/** Heredoc **/
void		*ft_heredoc(t_prog *msh);
void		generate_random_file(char **temp, int *hd_fd);
char		*hd_strjoin(char const *s1, char const *s2);
void		rm_end_spaces(char *str);
char		*find_heredoc(char *str);
char		*find_delim(char *str, t_heredoc *heredoc);
char		*hd_error(char *delim);
int			ctrlc_heredoc(int save_in);

#endif
