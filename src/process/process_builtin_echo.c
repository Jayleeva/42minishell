/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/01 13:28:08 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void    print_in_output(t_data *data, char *s, int n_flag)
{
    ft_putstr_fd(s, data->cmd->outfile);
    if (!n_flag)
        ft_putchar_fd('\n', data->cmd->outfile);
}

void    process_echo(t_data *data, char **argv)
{
    char    *s;
    char    *temp;
    int     i;
    int     n_flag;

    n_flag = 0;
    s = ft_strdup("");
    data->exit_code = 0;
    i = 1;
    if (!ft_strncmp(argv[1], "-n", 2))
    {
        i = 2;
        n_flag = 1;
    }
    while (argv[i])
    {
        temp = ft_strdup(argv[i]);
        s = ft_strjoin(s, temp);
        if (argv[i + 1])
            s = ft_strjoin(s, " ");
        free(temp);
        i ++;
    }
    print_in_output(data, s, n_flag);
    free(s);
}
