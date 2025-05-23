/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:25:48 by yishan            #+#    #+#             */
/*   Updated: 2025/05/12 15:53:47 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

static void	copy_token(char *input, int length, char *str, int i)
{
	int		j;
	char	quote_char;

	j = 0;
	quote_char = 0;
	while (i < length && input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			quote_char = input[i++];
			while (i < length && input[i] && input[i] != quote_char)
				str[j++] = input[i++];
			if (i < length && input[i] == quote_char)
				i++;
		}
		else
			str[j++] = input[i++];
	}
	str[j] = '\0';
}

static int	command_length(char *input, int *quotes)
{
	int		i;
	char	quote_char;

	i = 0;
	(*quotes) = 0;
	while (input[i] && !ft_is_space(input[i]) && !ft_is_special(input + i))
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			(*quotes)++;
			quote_char = input[i];
			i++;
			while (input[i] && input[i] != quote_char)
				i++;
			if (input[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}

static t_bool	add_command(t_token **head, char **input)
{
	int		quotes;
	int		length;
	int		i;
	char	*str;

	i = 0;
	length = command_length(*input, &quotes);
	if (((length) - (2 * quotes)) < 0)
		return (TRUE);
	str = ft_calloc(sizeof(char), ((length + 1) - quotes));
	if (!str)
		return (FALSE);
	copy_token(*input, (length - quotes), str, i);
	if (!token_put_in(head, str, CMD))
	{
		free(str);
		return (FALSE);
	}
	free(str);
	*input += length;
	return (TRUE);
}

static t_bool	add_special(t_token **head, char **input)
{
	int	type;

	type = ft_is_special(*input);
	if (!type)
		return (FALSE);
	if (type == HEREDOC && !token_put_in(head, "<<", HEREDOC))
		return (FALSE);
	else if (type == INPUT && !token_put_in(head, "<", INPUT))
		return (FALSE);
	else if (type == OUTPUT && !token_put_in(head, ">", OUTPUT))
		return (FALSE);
	else if (type == APPEND && !token_put_in(head, ">>", APPEND))
		return (FALSE);
	else if (type == PIPE && !token_put_in(head, "|", PIPE))
		return (FALSE);
	if (type == INPUT || type == OUTPUT || type == PIPE)
		(*input) += 1;
	else if (type == HEREDOC || type == APPEND)
		(*input) += 2;
	return (TRUE);
}

t_bool	create_token_list(t_token **head, char *input)
{
	while (*input)
	{
		while (ft_is_space(*input))
			input++;
		if (!*input)
			break ;
		if (ft_is_special(input))
		{
			if (!add_special(head, &input))
				return (FALSE);
		}
		else
		{
			if (!add_command(head, &input))
				return (FALSE);
		}
	}
	return (TRUE);
}
