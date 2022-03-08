
#include "minishell.h"

int main()
{
	char str[50];

	chdir("");
	getcwd(str, 50);

	printf("%s\n", str);
} 