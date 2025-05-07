/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:46:36 by yishan            #+#    #+#             */
/*   Updated: 2025/05/06 10:40:09 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

//$? = last exit code
//*str = "Error: " and buff = "1"
int	handle_special_case(t_data *data, char **buffer, char special_char)
{
	char	*value_str;
	char	*new_buffer;

	if (special_char == '?')
	{
		value_str = ft_itoa(data->exit_code);
		if (!value_str)
			return (0);
	}
	else if (special_char == '$')
	{
		value_str = ft_strdup("0");
		if (!value_str)
			return (0);
	}
	new_buffer = ft_strjoin(*buffer, value_str);
	free(value_str);
	if (!new_buffer)
		return (0);
	free(*buffer);
	*buffer = new_buffer;
	return (1);
}

int	handle_env_variable(t_data *data, char *input, int length, char **buffer)
{
	char	*var_name;
	char	*env_value;
	char	*new_buffer;
	char	*value_to_append;

	var_name = extract_var_name(input, length);
	if (!var_name)
		return (0);
	env_value = get_env_value(data->env, var_name);
	free(var_name);
	if (!env_value)
		return (0);
	value_to_append = env_value;
	if (value_to_append == NULL)
		value_to_append = "";
	new_buffer = ft_strjoin(*buffer, value_to_append);
	if (env_value)
		free(env_value);
	if (!new_buffer)
		return (0);
	free(*buffer);
	*buffer = new_buffer;
	return (1);
}

int	put_dollar(char *input, int *i, char **buffer, t_data *data)
{
	int		value;
	int		org_i;
	char	special_char;

	write(1, "-D-\n", 4);
	org_i = *i;
	value = check_env_variable(input, i, data);
	if (value == 1)
	{
		
		return (handle_env_variable(data, &input[org_i],
				*i - org_i, buffer));
	}
	else if (value == 2)
	{
		
		special_char = input[*i + 1];
		*i += 2;
		return (handle_special_case(data, buffer, special_char));
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

	write(1, "-E-\n", 4);
	if (current_char[0] == '$' && !data->quote.single_quote
		&& check_env_variable(current_char, i, data))
	{
		return (1);
	}	
	char_str[0] = current_char[0];
	char_str[1] = '\0';
	(*i)++;
	new_buffer = ft_strjoin(*buffer, char_str);
	if (!new_buffer)
	{
		return (0);
	}
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
		write(1, "-A-\n", 4);
		handle_quotes((*input)[i], &data->quote);
		/*if (data->quote.double_quote || data->quote.single_quote)
			j = 1;*/
		if ((*input)[i] == '$')																		// if input has a $
		{
			write(1, "-B-\n", 4);
			if ((*input)[i + 1] &&				 													// if there's a char after, and	
			(ft_isalpha((*input)[i + 1]) || (*input)[i + 1] == '?' || (*input)[i + 1] == '_') &&	// that char is either a letter, a ? or a _, and 
			!data->quote.single_quote &&															// there is no single quote, and
			!put_dollar((*input), &i, &str, data))													// put_dollar didn't work? worked?, then
				return (0);																			// dollar_handle worked.
		}
		if ((*input)[i] && !put_character(&(*input)[i], &str, data, &i))							// if there's a char, and put_character didn't worked? worked?, then
		{	
			write(1, "-C-\n", 4);
			return (0);																				// dollar_handle worked.
		}
		//j ++;	
		write(1, "-H-\n", 4);																					
	}
	free((*input));
	(*input) = str;
	return (1);																						// wasn't stopped before: means it didn't work.
}

