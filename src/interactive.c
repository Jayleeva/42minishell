/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:32:09 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/01 12:20:11 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

volatile sig_atomic_t   *g_sig;

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
    *g_sig = (sig_atomic_t)sig;
	if (sig == SIGINT) //ctrl c: give back command;
        reset_prompt();
	else if (sig == SIGQUIT) // ctrl \\:
	{
        /*if (blocking command / child process)
            kill(info->si_pid, );*/
            ft_printf("Quit (core dumped)"); // only if blocking command (child process!!!) if not, do nothing.
	}
    //usleep(1000);
}

void    minishell_interactive(t_data *data)
{
    char                *input;
	sigset_t			set;
	struct sigaction	shell;
    sig_atomic_t        toto;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	shell.sa_flags = SA_SIGINFO | SA_RESTART;
	shell.sa_mask = set;
	shell.sa_sigaction = &handle_signal;
    toto = 0;
    g_sig = &toto;
    while (1)
	{

        sigaction(SIGINT, &shell, NULL);
        sigaction(SIGQUIT, &shell, NULL);
        //wait(&status du child); je connais pas le status du child + pour que ça marche, supprimer SA_RESTART des flags
        if (*g_sig != 0)
        {
            data->exit_code = 128 + (int)*g_sig;
            *g_sig = 0;
            printf("exit code: %d\n", data->exit_code);
        }
        input = NULL;
        input = readline("minishell> ");
        if (!input)
            process_exit(data);  // Handle EOF (Ctrl+D)
        if (*input)
		{
            add_history(input);
            process_input(data, input);
            execute_pipeline(data);
            token_clear(&(data->token));
			cmd_clear(&data->cmd);
        }
		else
		{
			free(input);
			input = NULL;
		}
    }
    input = NULL;
}
