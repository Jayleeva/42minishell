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


void    preprocess_cd(t_data *data, t_token *current)
{
    if (!current->next) // si pas d'argument donné, retour à HOME.
    {
        chdir(get_env_value(data->env, "HOME"));
        return ;
    }
    if (current->next->next)
        ft_printf("minishell: cd: too many arguments\n");
    process_cd(current->next->str, data);
}

void    preprocess_export(t_data *data, t_token *current)
{
    if (!current->next)
        display_export(data);
    else
        process_export(current->next->str, data);
}

void    preprocess_unset(t_data *data, t_token *current)
{
    if (!current->next)
        return ;
    process_unset(current->next->str, data);
}

void    preprocess_echo(t_data *data, t_token *current)
{
    if (!current->next) //si pas d'arguments donné, imprime juste un retour à la ligne.
        ft_printf("\n");
    else if (current->next && !ft_strncmp(current->next->str, "-n", 2) && !current->next->next) //si flag -n mais pas d'argument après, imprime vide (sans retour à la ligne).
        ft_printf("");
    else
        process_echo(current->next, data);
}


void    process_token_list(t_data *data, t_token *token_list)
{
    t_token *current;

    current = token_list;
    if (current->type != CMD)
    {
        ft_printf("minishell: %s: command not found\n", current->str);
        return ;
    }
    if (!ft_strncmp(current->str, "exit", 5)) 
        process_exit();
    else if (!ft_strncmp(current->str, "pwd", 4))
        process_pwd(data);
    else if (!ft_strncmp(current->str, "env", 4))
        process_env(data);
    else if (!ft_strncmp(current->str, "cd", 2))
        preprocess_cd(data, current);
    else if (!ft_strncmp(current->str, "export", 6))
        preprocess_export(data, current);
    else if (!ft_strncmp(current->str, "unset", 5))
        preprocess_unset(data, current);
    else if (!ft_strncmp(current->str, "echo", 4))
        preprocess_echo(data, current);
    else if (!ft_strncmp(current->str, "$?", 3))
        ft_printf("%d\n", data->exit_code);
    else
        process_other(current->str, data);
}