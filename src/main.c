/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:27:40 by yisho             #+#    #+#             */
/*   Updated: 2025/04/29 16:37:20 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_data.h"
#include "../inc/linked_list.h"
#include "../libft/inc/libft.h"

// Parse the input and execute the corresponding commands
//tokenizing the input, handling pipes, redirections, etc.
t_bool	process_input(t_data *data, char *input)
{
	if (!check_open_quotes(data, input))
	{
		free(input);
		return (FALSE);
	}
	if (!dollar_handle(&input, data) ||!create_token_list(&data->token, input))
	{
		free(input);
		token_clear(&(data->token));
		return (FALSE);
	}
	//print_token_list(data->token);
	if (!data->token || !check_pipe_syntax(data) || !create_cmd_list(data))
	{
		free(input);
		token_clear(&(data->token));
		cmd_clear(&data->cmd);
		return (FALSE);
	}
	//print_cmd(data->cmd);
	free(input);
	return (TRUE);
}

int	count_var(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i ++;
	return (i);
}

t_env	*init_env(char **envp, int nvar)
{
	int		i;
	t_env	*env;
	t_env	*current;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->var = envp[0];
	env->next = NULL;
	i = 1;
	current = env;
	while (i < nvar)
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_env *)malloc(sizeof(t_env));
		if (current->next == NULL)
			return (NULL);
		current->next->var = envp[i];
		current->next->next = NULL;
		i ++;
	}
	return (env);
}

void	init_data(t_data *data)
{
	data->exit_code = 0;
	data->paths = NULL;
	data->token = NULL;
	data->env = NULL;
	data->export = NULL;
	data->cmd = NULL;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->last_pid = 0;
}

int main(int argc, char **argv, char **envp) 
{
    t_data  data;
	int		nvar;

	(void)argv;
    if (argc == 3)
		return (1);
	init_data(&data);
	nvar = count_var(envp);
	data.env = init_env(envp, nvar);
	data.export = init_env(envp, nvar);
	minishell_interactive(&data);
	return (0);
}
