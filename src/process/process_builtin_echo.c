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
    t_token *cur_str;

	data->exit_code = 0;
    s = NULL;
    cur_str = str;
    while (cur_str)
    {
        if (str->str[0] == '$' && str->str[1] != '?')
        {
            s = get_env_value(data->env, ft_substr(str->str, 1, ft_strlen(str->str)));
            if (!s)
                s = ft_strdup("");
        }
        else
            s = ft_strdup(str->str);
        ft_printf("%s\n", s);
        free(s);
        cur_str = cur_str->next;
    }
}
