/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/04/24 12:46:07 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../inc/linked_list.h"
#include "../../libft/inc/libft.h"

void    process_token_list(t_data *data, t_token *token_list)
{
    t_token *current;

    current = token_list;
    if (!ft_strncmp(current->str, "exit", 5)) 
        process_exit(data);
    else if (!ft_strncmp(current->str, "pwd", 4))
        process_pwd(data);
    else if (!ft_strncmp(current->str, "env", 4))
        process_env(data, current);
    else if (!ft_strncmp(current->str, "cd", 2))
        process_cd(data, current);
    else if (!ft_strncmp(current->str, "export", 6))
        process_export(data, current);
    else if (!ft_strncmp(current->str, "unset", 5))
        process_unset(data, current);
    else if (!ft_strncmp(current->str, "echo", 4))
        process_echo(data, current);
    else if (!ft_strncmp(current->str, "$?", 3))
        process_dollar(data);
    else
        process_other(current->str, data);
}