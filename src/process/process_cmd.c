/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/01 15:01:57 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../inc/linked_list.h"
#include "../../libft/inc/libft.h"

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

void    process_token_list(t_data *data, t_cmd *cmd)
{
    if (!ft_strncmp(cmd->argv[0], "exit", 5)) 
        process_exit(data);
    else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
        process_pwd(data);
    else if (!ft_strncmp(cmd->argv[0], "env", 4))
        process_env(data, cmd->argv);
    else if (!ft_strncmp(cmd->argv[0], "cd", 2))
        process_cd(data, cmd->argv);
    else if (!ft_strncmp(cmd->argv[0], "export", 6))
        process_export(data, cmd->argv);
    else if (!ft_strncmp(cmd->argv[0], "unset", 5))
        process_unset(data, cmd->argv);
    else if (!ft_strncmp(cmd->argv[0], "echo", 4))
        process_echo(data, cmd->argv);
    else
        process_other(cmd->argv[0], data);
}