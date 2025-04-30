/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_other.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/04/14 15:35:16 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../inc/linked_list.h"
#include "../../libft/inc/libft.h"

void    process_exit(t_data *data)
{
    data->exit_code = 0;
    ft_printf("exit\n");
    update_env(data->env, "SHLVL", "-1");
    exit (0);
}

void    process_dollar(t_data *data)
{
    ft_printf("%d\n", data->exit_code);
    //data->exit_code = 127;
}

void    process_other(char *cmd, t_data *data)
{
    data->exit_code = 127;
    ft_printf("%s: commmand not found\n", cmd);
}


void    update_env(t_env *env, char *name, void *new_value)
{
    t_env   *current;

    write(1, "-A-\n", 4);
    current = env;
    while (!current)
    {
        write(1, "-B-\n", 4);
        if (!ft_strncmp(current->name, name, ft_strlen(name)))
        {
            write(1, "-C-\n", 4);
            current->value = new_value;
            /*if (!ft_strncmp(name, "SHLVL", 5))
            {
                i = strchri(current->var, '=');
                value = ft_substr(current->var, i +1, ft_strlen(current->var));
                shlvl = ft_atoi(value) + ft_atoi(&new_value);
                current->var = ft_strdup("SHLVL=");
                current->var = ft_strjoin(current->var, ft_itoa(shlvl));
            }*/
        }
        current = current->next;
    }
    write(1, "-D-\n", 4);
}