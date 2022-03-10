/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:42 by ntan              #+#    #+#             */
/*   Updated: 2022/03/10 18:38:46 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"


// STRUCTURE POUR CHAQUE COMMANDE
typedef struct	s_block
{
	char		*input;
	char		*cmd;
	char		*output;
	int			fd[2];
	int			pid;
}				t_block;

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
	int			output_error;
	char 		**envp;
	t_list		*cmds; /** pointe sur des t_block cmds->content = t_block, cmds-next = le prochain chainon **/
	t_list		*garbage;
}				t_prog;

/** FONCTION DEMMARAGE ET FIN**/
void	init_prog(t_prog *minishell, char **envp);
void	destroy(t_prog *prog);

/** FONCTIONS DE PARSING **/
void	ft_process_line(char *line, t_prog *minishell);


#endif