/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/26 13:08:31 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../inc/token.h"
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
    s = cutstr(cmd, cmd[0], " "); //là, pris que le premier mot: incomplet car si pipe, premier peut etre juste
    if (s == NULL)
        s = ft_strdup(cmd);
    ft_strlcat(s, ": command not found", ft_strlen(s) + 20);
    data->exit_code = 127;
    ft_printf("%s\n", s);
    free(s);
}

void    process_cmd(char *cmd, t_data *data, char ***envp)
{
    if (ft_strncmp(cmd, "exit", 5) == 0)
        process_exit();
    else if (ft_strncmp(cmd, "pwd", 4) == 0)
        process_pwd(data);
    else if (ft_strncmp(cmd, "cd", 2) == 0)
        process_cd(cmd, data);
    else if (ft_strncmp(cmd, "echo", 4) == 0)
        process_echo(cmd, data);
    else if (ft_strncmp(cmd, "env", 4) == 0)
        process_env(data, envp);
    /*else if (ft_strncmp(cmd, "export", 6) == 0)
        process_export(cmd, data, envp);*/
    /*else if (ft_strncmp(cmd, "unset", 6) == 0)
        process_unset(cmd);*/
    else if (ft_strncmp(cmd, "$?", 3) == 0)
        ft_printf("%d\n", data->exit_code);
    else
        process_other(cmd, data);
}
