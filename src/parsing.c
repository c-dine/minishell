

#include "../minishell.h"

void	ft_process_line(char *line, t_prog *minishell)
{
	char 	**split_line;
	int		i;
	void	*temp;

	printf("\033[0;37m");
	split_line = ft_split(line, '|');
	if (split_line == NULL)
		exit(1);
	i = 0;
	while(split_line[i])
	{
		temp = ft_lstnew(split_line[i]);
		if (i == 0)
			minishell->cmds = temp;
		else
			ft_lstadd_back(&minishell->cmds, temp);
		i++;
	}
}
