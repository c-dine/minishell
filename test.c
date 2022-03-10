
#include "minishell.h"

int main()
{
	void	*tmp;
	char	str[6] = "hello";

	tmp = str;
	printf("%s", (char *)tmp);
	return (0);
} 