/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:32:09 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/08 16:34:02 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

volatile sig_atomic_t	*g_sig;

void	reset_prompt(void)
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
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		reset_prompt();
	}
}

void	init_signals(void)
{
	sigset_t			set;
	struct sigaction	shell;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	shell.sa_flags = SA_SIGINFO | SA_RESTART;
	shell.sa_mask = set;
	shell.sa_sigaction = &handle_signal;
	sigaction(SIGINT, &shell, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_input(t_data *data, char *input)
{
	if (!input)
	{
		data->exit_code = 0;
		ft_printf("exit\n");
		free_all(data, data->exit_code);
	}
	if (*input)
	{
		add_history(input);
		process_input(data, input);
		execute_pipeline(data);
		token_clear(&(data->token));
		cmd_clear(&data->cmd);
	}
}

void	minishell_interactive(t_data *data)
{
	char				*input;
	sig_atomic_t		sig;

	sig = 0;
	g_sig = &sig;
	init_signals();
	while (1)
	{
		input = NULL;
		input = readline("minishell> ");
		if (sig != 0)
		{
			data->exit_code = 128 + (int)sig;
			sig = 0;
		}
		if (!input || *input)
			handle_input(data, input);
		else
		{
			free(input);
			input = NULL;
		}
	}
	input = NULL;
}
