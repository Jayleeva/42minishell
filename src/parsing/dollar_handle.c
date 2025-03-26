/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:46:36 by yishan            #+#    #+#             */
/*   Updated: 2025/03/24 22:47:52 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../inc/token.h"
#include "../../libft/inc/libft.h"

/*current_char Pointer to current character position in input string
buffer Double pointer to the string buffer being built
Pointer to the shell data structure
index Pointer to the current index in input string
int 1 on success, 0 on failure (memory allocation)*/
int	append_character(char *current_char, char **buffer,
				t_data *data, int *index)
{
	char	char_str[2];
	char	*new_buffer;

	if (current_char[0] == '$' && !data->quote.single_quote
		&& environment_variable_exists(current_char, index, data))
		return (1);
	char_str[0] = current_char[0];
	char_str[1] = '\0';
	(*index)++;
	new_buffer = ft_strjoin(*buffer, char_str);
	if (!new_buffer)
		return (0);
	free(*buffer);
	*buffer = new_buffer;
	return (1);
}

int	dollar_handle(char **line, t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	data->quote.single_quote = FALSE;
	str = ft_strdup("");
	while ((*line)[i])
	{
        // Maintain exact quoting behavior from original
        if ((*line)[i] == '"' && !data->quote.single_quote)
            data->quote.double_quote = !data->quote.double_quote;
        if ((*line)[i] == '\'' && !data->quote.double_quote)
            data->quote.single_quote = !data->quote.single_quote;
		if ((*line)[i] && (*line)[i + 1] && (*line)[i] == '$' &&
			((*line)[i + 1] != '\'' && (*line)[i + 1] != '"') &&
			(ft_isalpha((*line)[i + 1]) || (*line)[i + 1] == '?' ||
			(*line)[i + 1] == '_') && !data->quote.single_quote &&
			!add_dollar((*line), &i, &str, data))
			return (0);
		if ((*line)[i] && !append_character(&(*line)[i], &str, data, &i))
			return (0);
	}
	free(*line);
	*line = str;
	return (1);
}