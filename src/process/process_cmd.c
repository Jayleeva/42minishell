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
    data->exit_code = 127;
    s = ft_strjoin(cmd, ": command not found");
    if (!s)
        return ;
    ft_printf("%s\n", s);
    free(s);
}


int ft_isnum(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return (0);
        i ++;
    }
    return (1);
}

void    process_token_list(t_data *data, t_token *token_list)
{
    t_token *current;
    //char    *cmd;

    current = token_list;
    /*cmd = NULL;
    if (current->next && ft_strncmp(current->next->str, "|", 1))
    {
        ft_printf("%s: too many arguments\n", cmd);
        return ;
    }*/
    
    if (!ft_strncmp(current->str, "exit", 5)) 
        process_exit();
    else if (!ft_strncmp(current->str, "pwd", 4))
        process_pwd(data);
    else if (!ft_strncmp(current->str, "env", 4))
        process_env(data);
    else if (!ft_strncmp(current->str, "cd", 2))
    {
        if (!current->next) // si pas d'argument donné, retour à HOME.
        {
            chdir(get_home(data));
            return ;
        }
        process_cd(current->next->str, data);
    }
    else if (!ft_strncmp(current->str, "export", 6))
    {
        if (!current->next)
            return;
        process_export(current->next->str, data);
    }
    else if (!ft_strncmp(current->str, "unset", 5))
    {
        if (!current->next)
            return;
        process_unset(current->next->str, data);
    }
    else if (!ft_strncmp(current->str, "echo", 4))
    {
        if (!current->next)
            ft_printf("\n");
        else
            process_echo(current->next, data);
    }
    else if (!ft_strncmp(current->str, "$?", 3))
        ft_printf("%d\n", data->exit_code);
    else
        process_other(current->str, data);
}