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
	else if (sig == SIGQUIT) // ctrl \\: if blocking command: kill child process; if not, do nothing
	{
        /*if (blocking command)
            kill(info->si_pid, );
        else*/
		ft_printf("ctrl \\: if blocking command: kill child process; if not, do nothing\n");
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
            if (!process_input(data, input))
                return ;
            //if(!execute_pipeline(&data)) waiting for the exec files
            //    return ;
            process_token_list(data, data->token);
            //cmd_clear(&data->cmd); double free!
            token_clear(&(data->token));
        }
        free(input);
    }
    free(input);
    input = NULL;
}
