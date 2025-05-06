/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_other.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/06 15:22:41 by yisho            ###   ########.fr       */
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
    //update_env(data->env, "SHLVL", "-1");
    exit (0);
}

/*void    process_other(char *cmd, t_data *data)
{
    data->exit_code = 127;
    printf_fd("STDERR_FILENO, %s: commmand not found\n", cmd);
}*/
