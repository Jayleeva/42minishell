/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:03:06 by yishan            #+#    #+#             */
/*   Updated: 2025/04/10 15:15:26 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

//Failed redirection → skip_cmd=true
//Invalid syntax → Exit with error code
static t_bool	setup_command(t_data *data, t_token *token)
{
	if (data->cmd->prev && !setup_command_input(data, token, data->cmd->prev)
		&& data->cmd->prev->infile != -1)
		return (FALSE);
	if (data->cmd->prev && data->cmd->prev->infile == -1)
	{
		data->cmd->prev->skip_cmd = TRUE;
		data->cmd->prev->outfile = -1;
		return (TRUE);
	}
	if (data->cmd->prev && !setup_command_output(data, token, data->cmd->prev)
		&& data->cmd->prev->outfile != -1)
		return (FALSE);
	if (data->cmd->prev && data->cmd->prev->outfile == -1)
	{
		if (data->cmd->prev->infile >= 0)
			close(data->cmd->prev->infile);
		data->cmd->prev->skip_cmd = TRUE;
		data->cmd->prev->infile = -1;
		return (TRUE);
	}
	data->cmd->prev->argv = get_command_arg(data, token);
	if (!data->cmd->prev->argv)
		cmd_clear((&data->cmd));
	return (TRUE);
}

static t_bool	process_command(t_data *data, t_token *current)
{
	printf("hello\n");
	if (!cmd_put_in(&data->cmd, -2, -2, NULL))
		cmd_clear((&data->cmd));
	if (!setup_command(data, current))
	{
		data->exit_code = 1;
		return (FALSE);
	}
	printf("hello\n");
	return (TRUE);
}

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
		token_clear(&data->token);
		return (FALSE);
	}
	last = token_getlast(data->token);
	if (!last)
		return (FALSE);
	if (last && last->type == PIPE)
	{
		ft_printf("Error: Unclosed pipe\n");
		data->exit_code = 1;
		token_clear(&data->token);
		return (FALSE);
	}
	return (TRUE);
}
