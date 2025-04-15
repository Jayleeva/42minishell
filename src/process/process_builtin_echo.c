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

void    process_echo(char *str, t_data *data)
{
    char    *s;
    t_env	*current;

	data->exit_code = 0;
    s = NULL;
    /*if (str[4] == '\0')
        ft_printf("\n");
    s = ft_substr(str, 5, ft_strlen(str));*/
    if (str[0] == '$')
    {
        current = data->env;
        while (current->next != NULL)
        {
            if (!ft_strncmp(current->var, ft_substr(str, 1, ft_strlen(s)), strchri(current->var, '=')))
                break;
            current = current->next;
        }
        if (!ft_strncmp(current->var, ft_substr(str, 1, ft_strlen(s)), strchri(current->var, '=')))
            s = ft_strdup(current->var);
        s = ft_strdup(current->var);
    }
    ft_printf("%s\n", s);
    free(s);
}
