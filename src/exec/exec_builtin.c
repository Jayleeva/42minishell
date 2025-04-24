/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:14:02 by yishan            #+#    #+#             */
/*   Updated: 2025/04/24 16:02:53 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

t_bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	return (ft_strncmp("cd", cmd, 3) || \
			ft_strncmp("echo", cmd, 5) || \
			ft_strncmp("pwd", cmd, 4) || \
			ft_strncmp("export", cmd, 7) || \
			ft_strncmp("unset", cmd, 6) || \
			ft_strncmp("env", cmd, 3) || \
			ft_strncmp("exit", cmd, 5));
}

/*static void	executing_built_in(int out, t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->argv[0], 4))
		data->exit_code = preprocess_echo(data, );
	else if (!ft_strncmp("cd", cmd->argv[0], INT_MAX))
		data->exit_code = preprocess_cd(data, current);
	else if (!ft_strncmp("pwd", cmd->argv[0], INT_MAX))
		data->exit_code = process_pwd(data);
	else if (!ft_strncmp("export", cmd->argv[0], INT_MAX))
		data->exit_code = preprocess_export(data, current);
	else if (!ft_strncmp("unset", cmd->argv[0], INT_MAX))
		data->exit_code = preprocess_unset(data, current);
	else if (!ft_strncmp("env", cmd->argv[0], INT_MAX))
		data->exit_code = process_env(data);
	else if (!ft_strncmp("exit", cmd->argv[0], INT_MAX))
	{
		if (cmd->outfile >= 0)
		{
			dup2(out, 1);
			close (out);
		}
		process_exit();
	}
}*/

/*void    process_token_list(t_data *data, t_token *token_list)
{
    t_token *current;

    current = token_list;
    if (current->type != CMD)
    {
        ft_printf("minishell: %s: command not found\n", current->str);
        return ;
    }
    if (!ft_strncmp(current->str, "exit", 5)) 
        process_exit();
    else if (!ft_strncmp(current->str, "pwd", 4))
        process_pwd(data);
    else if (!ft_strncmp(current->str, "env", 4))
        process_env(data);
    else if (!ft_strncmp(current->str, "cd", 2))
        preprocess_cd(data, current);
    else if (!ft_strncmp(current->str, "export", 6))
        preprocess_export(data, current);
    else if (!ft_strncmp(current->str, "unset", 5))
        preprocess_unset(data, current);
    else if (!ft_strncmp(current->str, "echo", 4))
        preprocess_echo(data, current);
    else if (!ft_strncmp(current->str, "$?", 3))
        ft_printf("%d\n", data->exit_code);
    else
        process_other(current->str, data);
}*/

t_bool	execute_builtin(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	int	out;

	out = -1;
	if (cmd->outfile >= 0)
	{
		out = dup(1);
		dup2(cmd->outfile, 1);
	}
	//executing_built_in(out, data, cmd);
	if (cmd->outfile >= 0)
	{
		dup2(out, 1);
		close (out);
	}
	return (TRUE);
}
