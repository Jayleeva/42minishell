/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:27:40 by yisho             #+#    #+#             */
/*   Updated: 2025/03/28 10:55:11 by yishan           ###   ########.fr       */
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
		return (FALSE);
	}
	if (!dollar_handle(&input, data) || !create_token_list(&data->token, input))
	{
		token_clear(&(data->token));
		return (FALSE);
	}
	print_token_list(data->token);
	token_clear(&(data->token));
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
	data->token = NULL;
	data->env = NULL;
}

int main(void) 
{
	char *input;
	t_data	data;

	init_data(&data);
	data.env = init_env(envp, nvar);
	//setup_environment(envp);
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
			{
				free(input);
				return (1);
			} 
		 }
		 //free(input);
	 }
	 // Cleanup before exit
	 //cleanup_environment();
	 return 0;
 }
