/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:32:09 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/15 15:03:01 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

volatile sig_atomic_t	*g_sig;

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	*g_sig = (sig_atomic_t)sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
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
		ft_printf("exit\n");
		ft_exit(data, 0);
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

void	interactive_utils(t_data *data, char *input)
{
	if (!input || *input)
		handle_input(data, input);
	else
	{
		free(input);
		input = NULL;
	}
}

void	minishell_interactive(t_data *data)
{
	char				*input;
	sig_atomic_t		sig;
	char				*buffer;

	sig = 0;
	g_sig = &sig;
	init_signals();
	while (1)
	{
		input = NULL;
		buffer = data->prompt;
		data->prompt = update_prompt(data->env);
		free(buffer);
		input = readline(data->prompt);
		if (sig != 0)
		{
			data->exit_code = 128 + (int)sig;
			sig = 0;
		}
		interactive_utils(data, input);
	}
	free(data->prompt);
	input = NULL;
}
