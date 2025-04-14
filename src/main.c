/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:27:40 by yisho             #+#    #+#             */
/*   Updated: 2025/04/14 12:46:38 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_data.h"
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
	print_token_list(data->token);
	if (!data->token || !check_pipe_syntax(data) || !create_cmd_list(data))
	{
		free(input);
		token_clear(&(data->token));
		cmd_clear(&data->cmd);
		return (FALSE);
	}
	print_cmd(data->cmd);
	cmd_clear(&data->cmd);
	token_clear(&(data->token));
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
	env->vartest = envp[0];
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
		current->next->vartest = envp[i];
		current->next->next = NULL;
		//ft_printf("%s\n", current->next->vartest);
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
	data->cmd = NULL;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->pid = 0;
}

int main(int argc, char **argv, char **envp) 
{
	char *input;
	int	nvar;
	t_data	data;
	(void)argv;
	(void)argc;

	init_data(&data);
	nvar = count_var(envp);
	data.env = init_env(envp, nvar);
	while (1) {
		// Display prompt and read input
		input = readline("minishell> ");
		if (!input) {
			printf("exit\n");
			break;
		}
		if (*input) {
			add_history(input);
			if(!process_input(&data, input))
				return (1);
			//if (!execute(&data))
			//free_all();
		}
		input = NULL;
	}
	// Cleanup before exit
	//cleanup_environment();
	return 0;
 }
