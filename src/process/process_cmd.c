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
    //s = ft_substr(cmd, 0, strchri(cmd, ' ') -1); //ADAPT ONCE TOKENS ARE WORKING AND INTEGRATED
    /*if (s == NULL)
        s = ft_strdup(cmd);*/
    data->exit_code = 127;
    s = ft_strjoin(cmd, ": command not found");
    if (!s)
        return ;
    ft_printf("%s\n", s);
    free(s);
}

void    process_token_list(t_data *data, t_token *token_list)
{
    t_token *current;

    current = token_list;
    if (current->type != 6)
        return ;
    
    if (!ft_strncmp(current->str, "exit", 5)) // si autre argument après, message d'erreur puis crash? vérifier dans bash
        process_exit();
    else if (!ft_strncmp(current->str, "pwd", 4)) //si autre argument après, l'ignore et agit normalement? vérifier dans bash
        process_pwd(data);
    else if (!ft_strncmp(current->str, "env", 4)) // si autre argument après est quelque chose qui n'existe pas, message d'erreur n'existe pas, si existe, rien ne se passe car pas d'environnement là-bas? vérifier dans bash
        process_env(data);
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
        process_echo(current->next->str, data);
    /*else if (!ft_strncmp(current->str, "$?", 3))
        ft_printf("%d\n", data->exit_code);*/
    else
        process_other(current->str, data);
}