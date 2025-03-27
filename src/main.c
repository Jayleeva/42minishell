/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:27:40 by yisho             #+#    #+#             */
/*   Updated: 2025/03/27 11:32:36 by cyglardo         ###   ########.fr       */
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
	if (!create_token_list(&data->token, input) /*|| !dollar_handle(&input, data)*/)
	{
		token_clear(&(data->token));
		return (FALSE);
	}
	print_token_list(data->token);
	token_clear(&(data->token));
	return (TRUE);
}

void	init_data(t_data *data)
{
	data->exit_code = 0;
	data->token = NULL;
	data->env = NULL;
}

int main(int argc, char **argv, char **envp)
{
    t_data  data;

	init_data(&data);
    if (argc == 3)
        return (1);
    /*if (init_env(envp))
        return (1);*/
    minishell_interactive(argc, argv, &data, &envp);
    return (0);
}