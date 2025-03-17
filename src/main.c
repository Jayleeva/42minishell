#include "../inc/minishell.h"
#include "../libft/inc/libft.h"

/*void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;

}*/

int	main(void)
{
	char 		*line_read = (char *)NULL;
	/*sigset_t			set;
	struct sigaction	shell;

	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	shell.sa_flags = SA_SIGINFO | SA_RESTART;
	shell.sa_mask = set;
	shell.sa_sigaction = &handle_signal;*/

	while (1)
	{
		line_read = readline("Enter a line: ");
		//add_history(line_read);
		if (ft_strncmp(line_read, "cd", 3) == 0)
			ft_printf("cd");
		if (ft_strncmp(line_read, "exit", 5) == 0)
			break;
	}
	//printf("%s\n", ttyname(1));
}
