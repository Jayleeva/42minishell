/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/04/14 11:30:03 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void    process_echo(t_token *str, t_data *data)
{
    char    *s;
    char    *temp;
    t_token *cur_str;

	data->exit_code = 0;
    s = "";
    temp = NULL;
    cur_str = str;
    while (cur_str && cur_str->type == ARG)
    {
        if (cur_str->str[0] == '$' && cur_str->str[1] != '?')
        {
            temp = get_env_value(data->env, ft_substr(cur_str->str, 1, ft_strlen(cur_str->str)));
            if (!temp)
                temp = ft_strdup("");
        }
        else
            temp = ft_strdup(cur_str->str);
        s = ft_strjoin(s, temp);
        if (cur_str->next && cur_str->next->type == ARG)
            s = ft_strjoin(s, " ");
        free(temp);
        cur_str = cur_str->next;
    }
    ft_printf("%s\n", s);
    free(s);
}
