/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:46:36 by yishan            #+#    #+#             */
/*   Updated: 2025/03/28 10:36:47 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

//static int	handle_env_variable(t_data *data, char *input, int size, char **str)


int	put_dollar(char *input, int *i, char **buffer, t_data *data)
{
	int	value;
	//int	org_i;

	//org_i = *i;
	value = check_env_variable(input, i, data);
	if (value == 1)
	{
		//return (handle_env_variable(data, &input[org_i],
		//		*i - org_i, buffer));
		return 1;
	}
	else if (value == 2)
	{
		*i += 2;
		return (handle_special_case(data, buffer));
	}
	else
	{
		(*i)++;
		while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
			(*i)++;
		return (1);
	}
}

// Convert char to string
int	put_character(char *current_char, char **buffer, t_data *data, int *i)
{
	char	char_str[2];
	char	*new_buffer;

	if (current_char[0] == '$' && !data->quote.single_quote
		&& check_env_variable(current_char, i, data))
		return (1);
	char_str[0] = current_char[0];
	char_str[1] = '\0';
	(*i)++;
	new_buffer = ft_strjoin(*buffer, char_str);
	if (!new_buffer)
		return (0);
	free(*buffer);
	*buffer = new_buffer;
	return (1);
}

int	dollar_handle(char **input, t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	data->quote.double_quote = FALSE;
	data->quote.single_quote = FALSE;
	str = ft_strdup("");
	while ((*input)[i])
	{
		handle_quotes((*input)[i], &data->quote);
		if ((*input)[i] && (*input)[i + 1] && (*input)[i] == '$' &&
			((*input)[i + 1] != '\'' && (*input)[i + 1] != '"') &&
			(ft_isalpha((*input)[i + 1]) || (*input)[i + 1] == '?' ||
			(*input)[i + 1] == '_') && !data->quote.single_quote &&
			!put_dollar((*input), &i, &str, data))
			return (0);
		if ((*input)[i] && !put_character(&(*input)[i], &str, data, &i))
			return (0);
	}
	free(*input);
	*input = str;
	return (1);
}

