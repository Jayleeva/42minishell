/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/01 14:48:08 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../inc/linked_list.h"
#include "../../libft/inc/libft.h"

void    process_token_list(t_data *data, t_cmd *cmd)
{
    if (!ft_strncmp(cmd->argv[0], "exit", 5)) 
        process_exit(data);
    else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
        process_pwd(data);
    else if (!ft_strncmp(cmd->argv[0], "env", 4))
        process_env(data, cmd->argv);
    else if (!ft_strncmp(cmd->argv[0], "cd", 2))
        process_cd(data, cmd->argv);
    else if (!ft_strncmp(cmd->argv[0], "export", 6))
        process_export(data, cmd->argv);
    else if (!ft_strncmp(cmd->argv[0], "unset", 5))
        process_unset(data, cmd->argv);
    else if (!ft_strncmp(cmd->argv[0], "echo", 4))
        process_echo(data, cmd->argv);
    else if (!ft_strncmp(cmd->argv[0], "$?", 3))
        process_dollar(data);
    else
        process_other(cmd->argv[0], data);
}