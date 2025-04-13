/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:03:06 by yishan            #+#    #+#             */
/*   Updated: 2025/04/13 16:35:06 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

//Failed redirection → skip_cmd=true
//Invalid syntax → Exit with error code
static t_bool	setup_command(t_data *data, t_token *token)
{
	t_cmd	*cmd;

	if (!data || !data->cmd)
		return (FALSE);
	cmd = data->cmd;
	while (cmd->next)
		cmd = cmd->next;
	if (!setup_command_input(data, token, cmd) || \
		!setup_command_output(data, token, cmd))
	{
		cmd->skip_cmd = TRUE;
		return (TRUE);
	}
	cmd->argv = get_command_arg(data, token);
	if (!cmd->argv)
	{
		cmd_clear(&data->cmd);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	process_command(t_data *data, t_token *current)
{
	if (data->cmd && !setup_command(data, current))
	{
		data->exit_code = 1;
		return (FALSE);
	}
	if (!cmd_put_in(&data->cmd, STDIN_FILENO, STDOUT_FILENO, NULL))
	{
		cmd_clear(&data->cmd);
		return (FALSE);
	}
	return (TRUE);
}

//parser splits tokens into command structures at each pipe (|)
//1st command is always valid, after the 1st one should only appear after a pipe
t_bool	create_cmd_list(t_data *data)
{
	t_token	*current;

	if (!data || !data->token)
		return (FALSE);
	current = data->token;
	if (!process_command(data, current))
		return (FALSE);
	current = current->next;
	while (current)
	{
		if (current->prev && current->prev->type == PIPE)
		{
			if (!process_command(data, current))
				return (FALSE);
		}
		current = current->next;
	}
	return (TRUE);
}

t_bool	check_pipe_syntax(t_data *data)
{
	t_token	*last;

	if (data->token && data->token->type == PIPE)
	{
		ft_printf("Error: Unexpected token '|'\n");
		data->exit_code = 1;
		return (FALSE);
	}
	last = token_getlast(data->token);
	if (!last)
		return (FALSE);
	if (last && last->type == PIPE)
	{
		ft_printf("Error: Unclosed pipe\n");
		data->exit_code = 1;
		return (FALSE);
	}
	return (TRUE);
}
