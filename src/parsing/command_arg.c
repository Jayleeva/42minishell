/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:23:45 by yishan            #+#    #+#             */
/*   Updated: 2025/04/10 15:16:23 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

//Determines if a token should be included as a command argument
static t_bool	is_valid_argument(const t_token *token, const t_token *head)
{
	t_bool	prev_is_special;
	t_bool	not_wrapped;

	if (token->type == CMD)
		return (TRUE);
	if (token->type == ARG)
	{
		prev_is_special = is_redirection(token->prev->type)
			|| token->prev->type == PIPE;
		not_wrapped = (token->prev != head->prev);
		return (not_wrapped && !prev_is_special);
	}
	return (FALSE);
}

//Counts valid arguments for command construction
static int	count_arguments(t_data *data, t_token *start_token)
{
	int		count;
	t_token	*current;

	count = 0;
	current = start_token;
	while (current != data->token && current->type != PIPE)
	{
		if (is_valid_argument(current, data->token))
			count++;
		current = current->next;
	}
	return (count);
}

static char	**free_args_array(char **args, int filled_count)
{
	if (!args)
		return (NULL);
	while (filled_count-- > 0)
		free(args[filled_count]);
	free(args);
	return (NULL);
}

/*builds the command array, Uses count_args() to allocate memory
Fills the array with valid command tokens*/
char	**get_command_arg(t_data *data, t_token *start_token)
{
	int		arg_count;
	int		i;
	char	**args;
	t_token	*current;

	i = 0;
	current = start_token;
	arg_count = count_arguments(data, start_token);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	while (current != data->token && current->type != PIPE)
	{
		if (is_valid_argument(current, data->token))
		{
			args[i] = ft_strdup(current->str);
			if (!args[i])
				free_args_array(args, i);
			i++;
		}
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}
