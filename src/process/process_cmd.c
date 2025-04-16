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

    current = token_list;
    if (current->type != 6)
        return ;
    
    if (!ft_strncmp(current->str, "exit", 5)) 
    {
        if (current->next && current->next->type == ARG)
        {
            if (ft_isnum(current->next->str))
            {
                if (current->next->next)
                {
                    ft_printf("exit\nminishell: exit: too many arguments\n");
                    return ;
                }
                ft_printf("exit\n");
                exit (ft_atoi(current->next->str) % 256);
            }
            else
            {
                ft_printf("exit\nminishell: exit: '%s': numeric argument required\n", current->next->str);
                exit (2);
            }
        }
        process_exit();
    }
    else if (!ft_strncmp(current->str, "pwd", 4)) //si autre argument après, l'ignore et agit normalement
        process_pwd(data);
    else if (!ft_strncmp(current->str, "env", 4)) // si autre argument après est quelque chose qui n'existe pas, message d'erreur n'existe pas, si existe, rien ne se passe car pas d'environnement là-bas? vérifier dans bash
    {
        if (current->next)
        {
            //if ()
            //  return;
            ft_printf("env: '%s': No such file or directory\n", current->next->str);
            return ;
        }    
        process_env(data);
    }
    else if (!ft_strncmp(current->str, "cd", 2))
    {
        if (!current->next) // si pas d'argument donné, retour à HOME.
        {
            chdir(get_home(data));
            return ;
        }
        if (current->next->next && ft_strncmp(current->next->next->str, "|", 1))
        {
            ft_printf("cd: too many arguments\n");
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
            return;
        process_echo(current->next, data);
    }
    else if (!ft_strncmp(current->str, "$?", 3))
        ft_printf("%d\n", data->exit_code);
    else
        process_other(current->str, data);
}