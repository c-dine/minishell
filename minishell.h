/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:42 by ntan              #+#    #+#             */
/*   Updated: 2022/03/21 15:20:31 by ntan             ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>

# define CMD_NOT_FOUND 0
# define FILE_NOT_FOUND 1
# define QUOTE_NOT_CLOSED 2
# define PARSE_ERROR 3
# define PERMISSION_DENIED 4

extern int error_code;

// STRUCTURE POUR CHAQUE COMMANDE
// typedef struct	s_block
// {
// 	char		**input;
// 	int			*input_fd;
// 	char		**cmd;
// 	char		**output;
// 	int			*output_fd;
// 	char		**outputs_append;
// 	int			*outputs_append_fds;
// 	int			fd[2];
// 	int			pid;
// }				t_block;

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// 	struct s_list	*prev;
// }					t_list;
/** STRUCTURE DE LA LISTE CHAINEE DANS LA LIBFT **/

// STRUCTURE DU PROGRAMME
typedef struct	s_prog
{
	char 		**envp;
	t_list		*cmds; /** pointe sur des t_block cmds->content = t_block, cmds-next = le prochain chainon **/
	t_list		*garbage;
	int			dup_fd_stdout;
}				t_prog;

/** FONCTION DEMMARAGE ET FIN**/
void	init_prog(t_prog *minishell, char **envp);
void	close_fds(t_prog *msh);
void	close_pipe(int *fd);
int		ft_process_line(char *line, t_prog *minishell);

/** FONCTIONS DE PARSING **/
int		ft_parsing(char *line, t_prog *minishell);
char	*replace_var(char *line, t_prog *msh);
void	ft_check_cmds(t_prog *msh);

/** LES SIGNAUX **/
void	signal_manager(int sig);

/** OPENS FUNCTIONS **/
int	open_fds(t_block *block);
int	open_pipes(t_block *block);


/** Fonctions utiles **/
char	**add_to_duotab(char **tab, char *element);
void	print_duotab(char **tab);
int		strlen_duotab(char **str);
int		ft_nblen(int nb);
char	*get_absolute_path(char *cmd, char **envp);

/** ERRORS **/
void	*ft_error(int code);

/** Builtin **/
void	ft_echo(char **cmd);

#endif
