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

int expand_dollar(t_data *data, char *name)
{
    char    *value;

    value = get_env_value(data->env, name);
    if (!value)
        return (0);
    data->expanded_input = ft_strjoin(data->expanded_input, value);
    return (ft_strlen(value));
}

char    *extract_word(char *input, int i, char *word)
{
    int start;

    start = i;
    if (input[i] == '$')
        start ++;
    while (input[i])
    {
        if (input[i] < 32)
            break;
        i ++;
    }
    word = ft_substr(input, start, i);
    return (word);
}

int dollar_handle(char *input, t_data *data)
{
    int     i;
    char    *word;

    i = 0;
    word = ft_strdup("");
    data->expanded_input = ft_strdup("");
    data->quote.double_quote = FALSE;
    data->quote.single_quote = FALSE;
    while (input[i])
    {
        handle_quotes(input[i], &data->quote);
        word = extract_word(input, i, word);
        if (input[i] == '$')
        {
            if (input[i + 1] &&                                                                 // if there's a char after, and 
            (ft_isalpha(input[i + 1]) || input[i + 1] == '?' || input[i + 1] == '_') &&         // that char is either a letter, a ? or a _, and 
            !data->quote.single_quote)                                                      // there is no single quote, then
                i += expand_dollar(data, word);                                             // expand_dollar 
        }
        else
        {
            data->expanded_input = ft_strjoin(data->expanded_input, word);
            i += ft_strlen(word);
        }
        if (input[i + 1])
        data->expanded_input = ft_strjoin(data->expanded_input, " ");
    }
    free(input);
    input = data->expanded_input;
    return (0);
}
