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
    exit (0);
}

void    process_dollar(t_data *data)
{
    ft_printf("%d\n", data->exit_code);
    data->exit_code = 127;
}

void    process_other(char *cmd, t_data *data)
{
    data->exit_code = 127;
    ft_printf("%s: commmand not found\n", cmd);
}

