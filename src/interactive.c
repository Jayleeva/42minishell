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

volatile sig_atomic_t   *g_exit_status;

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
    *g_exit_status = (sig_atomic_t)(128 + sig);
	if (sig == SIGINT)
    {
        reset_prompt();
        //ft_printf("ctrl c: give back command\n");
    }
	else if (sig == SIGQUIT)
	{
        /*if (blocking command)
            kill(info->si_pid, );
        else*/
		ft_printf("ctrl \\: if blocking command: kill child process; if not, do nothing\n");
	}
}

void    minishell_interactive(int argc, char **argv, t_data *data)
{
    //t_token             *head;
    char                *input;
	sigset_t			set;
	struct sigaction	shell;
    //char                **tab;
    sig_atomic_t        toto;

    (void)argc;
    (void)argv;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	shell.sa_flags = SA_SIGINFO | SA_RESTART;
	shell.sa_mask = set;
	shell.sa_sigaction = &handle_signal;
    toto = 0;
    g_exit_status = &toto;
    while (1)
	{
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
            if (!process_input(data, input))
                return ;
            //if(!execute_pipeline(&data)) waiting for the exec files
            //    return ;
            process_token_list(data, data->token);
            //cmd_clear(&data->cmd); double free!
            token_clear(&(data->token));
        }
		sigaction(SIGINT, &shell, NULL);
		sigaction(SIGQUIT, &shell, NULL);
        //pause();
        if (*g_exit_status != 0)
        {
            write(1, "HEY\n", 4);
            data->exit_code = *g_exit_status;
            *g_exit_status = 0;
        }
        free(input); // Free the input line after processing 
    }
    free(input);
    input = NULL;
}