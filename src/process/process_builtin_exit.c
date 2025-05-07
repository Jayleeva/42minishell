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

int isnum(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (0);
        i ++;
    }
    return (1);
}

void    process_exit(t_data *data, char **argv)
{
    data->exit_code = 0;
    if (argv[2])
        ft_putstr_fd("minishell: exit: too many arguments\n");
    if (argv[1])
    {
        if (!isnum(argv[1]))
        {
            ft_printf("exit\n");
            printf_fd(1, "minishell: exit: %s: numeric argument required\n", argv[1]);
            data->exit_code = 2;
            exit (2);
        }
        else
        {
            data->exit_code = ft_atoi(argv[1]) % 256;
            exit (data->exit_code);
        }
    }
    else
    {
        ft_printf("exit\n");
        exit (0);
    }
}