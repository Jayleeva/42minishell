#include "../inc/minishell.h"
#include "../libft/inc/libft.h"

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGINT)
		ft_printf("ctrl c: give back command");
	else if (sig == SIGQUIT)
	{
		ft_printf("ctrl \\: if blocking command: kill process; if not, do nothing");
	}
}

int	main(void)
{
	char 		*line_read = (char *)NULL;
	sigset_t			set;
	struct sigaction	shell;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	shell.sa_flags = SA_SIGINFO | SA_RESTART;
	shell.sa_mask = set;
	shell.sa_sigaction = &handle_signal;

	while (1)
	{
		sigaction(SIGINT, &shell, NULL);
		sigaction(SIGQUIT, &shell, NULL);
		line_read = readline("Enter a line: ");
		//add_history(line_read);
		if (ft_strncmp(line_read, "cd", 3) == 0)
			ft_printf("cd\n");
		if (ft_strncmp(line_read, "exit", 5) == 0)
			break;
	}
	//printf("%s\n", ttyname(1));
}
