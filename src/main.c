#include "../inc/minishell.h"
#include "../libft/inc/libft.h"

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGINT)
    {
        ft_printf("\n");
        //ft_printf("ctrl c: give back command\n");
    }
	else if (sig == SIGQUIT)
	{
		ft_printf("ctrl \\: if blocking command: kill process; if not, do nothing\n");
	}
}

/*void setup_environment(char **envp)
{
    // Setup environment variables, signal handlers, etc.

}*/

void process_input(char *input)
{
    // Parse the input and execute the corresponding commands
    // This might involve tokenizing the input, handling pipes, redirections, etc.
    if (ft_strncmp(input, "exit", 5) == 0)
    {
        ft_printf("exit\n");
        exit (0);
    }
    else if (ft_strncmp(input, "pwd", 4) == 0)
    {
        ft_printf("pwd\n");
    }
    //printf("Processing: %s\n", input);  // Placeholder for actual processing
}

/*void cleanup_environment()
{
    // Free any allocated resources, close files, etc.
}*/

int main(int argc, char **argv, char **envp)
{
    char *input;
    (void)argc;  // Unused parameters
    (void)argv;
    (void)envp;
	sigset_t			set;
	struct sigaction	shell;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	shell.sa_flags = SA_SIGINFO | SA_RESTART;
	shell.sa_mask = set;
	shell.sa_sigaction = &handle_signal;
    // Initialize anything you need here (e.g., environment setup, signal handling)
    //setup_environment(envp);
    while (1)
	{
		sigaction(SIGINT, &shell, NULL);
		sigaction(SIGQUIT, &shell, NULL);
        // Display prompt and read input
        input = NULL; // (re)initialize the input to avoid situations where it's uninitialized AND to reset it between every call
        input = readline("minishell> ");
        if (!input)
		{
            printf("exit\n");  // Handle EOF (Ctrl+D)
            break;
        }
        // If input is not empty, add to history and process
        if (*input)
		{
            add_history(input);
            process_input(input);  // Your function to parse and execute commands
        }
        free(input); // Free the input line after processing 
    }
    // Cleanup before exit
   // cleanup_environment();
    return 0;
}
