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
    t_env	*current;

	data->exit_code = 0;
    s = NULL;
    //ft_printf("HELLO %s puis %s\n", str->str, str->next->str);
    cur_str = str;
    while (cur_str->next)
    {
        if (str->str[0] == '$')
        {
            write(1, "HEY\n", 4);
            current = data->env;
            while (current->next != NULL)
            {
                if (!ft_strncmp(current->var, ft_substr(str->str, 1, ft_strlen(s)), strchri(current->var, '=')))
                    break;
                current = current->next;
            }
            if (!ft_strncmp(current->var, ft_substr(str->str, 1, ft_strlen(s)), strchri(current->var, '=')))
                s = ft_strdup(current->var);
            /*else
                s = ft_strdup("");*/
        }
        else
            s = ft_strdup(str->str);
        ft_printf("%s\n", s);
        free(s);
        cur_str = cur_str->next;
    }
}
