/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:32:09 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/05 11:03:23 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

volatile sig_atomic_t   *g_sig;

void    reset_prompt()
{
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
    {
        write(1, "\n", 1);
        reset_prompt();
    }
	else if (sig == SIGQUIT) // ctrl \\:
	{
        if (rl_line_buffer && *rl_line_buffer)
        {
            ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO); // only if blocking command! if not, do nothing.
            reset_prompt();
        }
	}
}

void    minishell_interactive(t_data *data)
{
    char                *input;
	sigset_t			set;
	struct sigaction	shell;
    sig_atomic_t        sig;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	shell.sa_flags = SA_SIGINFO | SA_RESTART;
	shell.sa_mask = set;
	shell.sa_sigaction = &handle_signal;
    //shell.sa_handler = SIG_IGN;
    sig = 0;
    g_sig = &sig;

    sigaction(SIGINT, &shell, NULL);
    //sigaction(SIGQUIT, &shell, NULL);
    signal(SIGQUIT, SIG_IGN); // ADAPT FOR CHILD!!!
    while (1)
	{
        input = NULL;
        input = readline("minishell> ");
        if (sig != 0)
        {
            data->exit_code = 128 + (int)sig;
            sig = 0;
        }
        if (!input) // Handle EOF (Ctrl+D)
        {
            data->exit_code = 0;
            exit (0);
        } 
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
