#include "../inc/minishell.h"
#include "../libft/inc/libft.h"

int	main(void)
{
	static char *line_read = (char *)NULL;
	line_read = readline("Enter a line: ");
	add_history(line_read);
	printf("%s\n", ttyname(1));
}