#include "../minishell.h"

void	ft_process_line(char *line, t_prog *minishell)
{
	char 	**split_line;
	int		i;

	printf("\033[0;37m");
	split_line = ft_split(line, '|');
	if (split_line == NULL)
		exit(1);
	while (split_line[i])
	{
		
	}
	(void) minishell;
	
}
