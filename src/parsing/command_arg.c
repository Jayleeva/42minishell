/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:23:45 by yishan            #+#    #+#             */
/*   Updated: 2025/04/25 14:30:10 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

static t_bool	is_valid_argument(const t_token *token)
{
	if (token->type != CMD && token->type != ARG)
		return (FALSE);
	if (token->prev && is_redirection(token->prev->type))
		return (FALSE);
	return (TRUE);
}

//Counts valid arguments for command construction
static int	count_arguments(t_token *start_token)
{
	int		count;
	t_token	*current;

	count = 0;
	current = start_token;
	while (current && current->type != PIPE)
	{
		if (is_valid_argument(current))
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
char	**get_command_arg(t_token *start_token)
{
	int		arg_count;
	int		i;
	char	**args;
	t_token	*current;

	i = 0;
	current = start_token;
	arg_count = count_arguments(start_token);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	while (current && current->type != PIPE)
	{
		if (is_valid_argument(current))
		{
			args[i] = ft_strdup(current->str);
			if (!args[i])
				return (free_args_array(args, i));
			i++;
		}
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

