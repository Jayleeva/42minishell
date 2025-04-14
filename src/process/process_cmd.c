/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
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

void    process_exit(void)
{
    ft_printf("exit\n");
    exit (0);
}

void    process_other(char *cmd, t_data *data)
{
    char    *s;

    s = NULL;
    s = ft_substr(cmd, 0, strchri(cmd, ' ') -1); //ADAPT ONCE TOKENS ARE WORKING AND INTEGRATED
    if (s == NULL)
        s = ft_strdup(cmd);
    ft_strlcat(s, ": command not found", ft_strlen(s) + 20);
    data->exit_code = 127;
    ft_printf("%s\n", s);
    free(s);
}
/*void    process_cmd(char **tab)
{
    t_token *current;

    current = head;
    if (!current)
        ft_printf("c'est nul en fait, duh\n");
    else
        ft_printf("meh\n");
    if (current->type != 6)
        return ;
    
    if (!ft_strncmp(current->str, "exit", 5))
        process_exit();
    else
        ft_printf("meh");
    while (current)
    {
        ft_printf("token = %d, %s\n", current->type, current->str);
        current = current->next;
    }
}*/

void    process_cmd(char *cmd, t_data *data)
{
    if (ft_strncmp(cmd, "exit", 5) == 0)
        process_exit();
    else if (ft_strncmp(cmd, "pwd", 4) == 0)
        process_pwd(data);
    else if (ft_strncmp(cmd, "cd", 2) == 0)
        process_cd(cmd, data);
    else if (ft_strncmp(cmd, "echo", 4) == 0)
        process_echo(cmd, data);
    else if (ft_strncmp(cmd, "env", 4) == 0)
        process_env(data);
    else if (ft_strncmp(cmd, "export", 6) == 0)
        process_export(cmd, data);
    else if (ft_strncmp(cmd, "unset", 5) == 0)
        process_unset(cmd, data);
    else if (ft_strncmp(cmd, "$?", 3) == 0)
        ft_printf("%d\n", data->exit_code);
    else
        process_other(cmd, data);
}
