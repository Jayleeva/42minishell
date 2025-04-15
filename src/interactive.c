/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:32:09 by cyglardo          #+#    #+#             */
/*   Updated: 2025/04/14 15:53:44 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

int   g_exit_status;

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
        g_exit_status = 130;
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

void    minishell_interactive(int argc, char **argv, t_data *data)
{
    //t_token             *head;
    char                *input;
	sigset_t			set;
	struct sigaction	shell;
    //char                **tab;

    (void)argc;
    (void)argv;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	shell.sa_flags = SA_SIGINFO | SA_RESTART;
	shell.sa_mask = set;
	shell.sa_sigaction = &handle_signal;
    data->exit_code = 0;
    g_exit_status = data->exit_code;
    while (1)
	{
		sigaction(SIGINT, &shell, NULL);
		sigaction(SIGQUIT, &shell, NULL);
        data->exit_code = g_exit_status;
        input = NULL; // (re)initialize the input to avoid situations where it's uninitialized AND to reset it between every call
        input = readline("minishell> ");
        if (!input)
		{
            printf("exit\n");  // Handle EOF (Ctrl+D)
            break;
        }
        if (*input) // If input is not empty, add to history and process
		{
            add_history(input);
            process_input(data, input);
            process_token_list(data, data->token);
            token_clear(&(data->token));
        }
        free(input); // Free the input line after processing 
    }
    free(input);
    input = NULL;
   // cleanup_environment(); // Cleanup before exit
}