#include "../inc/minishell.h"
#include "../libft/inc/libft.h"

t_sig   g_sig;

void    reset_prompt()
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
    (void)info;
	if (sig == SIGINT)
    {
        g_sig.exit_status = 130;
        reset_prompt();
        //ft_printf("ctrl c: give back command\n");
    }
	else if (sig == SIGQUIT)
	{
        /*if (blocking command)
            kill(info->si_pid, );
        else*/
		ft_printf("ctrl \\: if blocking command: kill process; if not, do nothing\n");
	}
}

void setup_environment(char **envp)
{
    // Setup environment variables, signal handlers, etc.
    (void)envp;
    g_sig.exit_status = 0;
}

/*void cleanup_environment()
{
    // Free any allocated resources, close files, etc.
}*/

void    minishell_interactive(int argc, char **argv, char **envp)
{
    char                *input;
	sigset_t			set;
	struct sigaction	shell;

    (void)argc;  // Unused parameters
    (void)argv;
    (void)envp;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	shell.sa_flags = SA_SIGINFO | SA_RESTART;
	shell.sa_mask = set;
	shell.sa_sigaction = &handle_signal;
    // Initialize anything you need here (e.g., environment setup, signal handling)
    setup_environment(envp);
    while (1)
	{
		sigaction(SIGINT, &shell, NULL);
		sigaction(SIGQUIT, &shell, NULL);
        input = NULL; // (re)initialize the input to avoid situations where it's uninitialized AND to reset it between every call
        input = readline("minishell> "); // Display prompt and read input
        if (!input)
		{
            printf("exit\n");  // Handle EOF (Ctrl+D)
            break;
        }
        if (*input) // If input is not empty, add to history and process
		{
            add_history(input);
            process_input(input);  // Your function to parse and execute commands
        }
        free(input); // Free the input line after processing 
    }
    input = NULL;
    // Cleanup before exit
   // cleanup_environment();
}

int main(int argc, char **argv, char **envp)
{
    if (argc == 3)
        return (1);
    minishell_interactive(argc, argv, envp);
    return 0;
}
