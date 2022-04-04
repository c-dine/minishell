/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:58:49 by cdine             #+#    #+#             */
/*   Updated: 2022/04/04 17:27:06 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
#include "libft/libft.h"
#include <stddef.h>
#include <stdlib.h>

int main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	char *tmp[] = {"gcc", "test1.c", NULL};

	execve("/usr/bin/gcc", tmp, envp);
}
