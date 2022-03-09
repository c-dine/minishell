/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:28:42 by ntan              #+#    #+#             */
/*   Updated: 2022/03/07 17:46:29 by ntan             ###   ########.fr       */
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

typedef struct	s_block
{
	char		*input;
	char		*cmd;
	char		*output;
}				t_block;

// typedef struct	s_linked
// {
// 	t_block		*trio;
// 	t_linked	next;
// 	t_linked	prev;
// }				t_linked;
/** STRUCTURE DE LA LISTE CHAINEE DANS LA LIBFT **/

typedef struct	s_prog
{
	int			output_error;
	char 		**envp;
	// t_list		*list;
	char		**cmd_tab;
}				t_prog;

/** FONCTION DEMMARAGE ET FIN**/
t_prog *init_prog();
void	destroy(t_prog *prog);


/** FONCTIONS DE PARSING **/
void	ft_process_line(char *line, t_prog *minishell);



#endif