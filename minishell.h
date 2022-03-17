/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:42 by ntan              #+#    #+#             */
/*   Updated: 2022/03/17 23:38:54 by cdine            ###   ########.fr       */
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
}				t_prog;

/** FONCTION DEMMARAGE ET FIN**/
void	init_prog(t_prog *minishell, char **envp);
void	close_fds(t_prog *msh);

/** FONCTIONS DE PARSING **/
int	ft_process_line(char *line, t_prog *minishell);
char	*replace_var(char *line, t_prog *msh);

/** LES SIGNAUX **/
void	signal_manager(t_prog *msh);

/** OPENS FUNCTIONS **/
int	open_fds(t_block *block);
int	open_pipes(t_block *block);


/** Fonctions utiles **/
char	**add_to_duotab(char **tab, char *element);
void	print_duotab(char **tab);
int		strlen_duotab(char **str);
int		ft_nblen(int nb);

/** ERRORS **/
void	*ft_error(int code);

#endif
