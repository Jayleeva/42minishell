/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_directory.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/05 11:21:42 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void    process_cd(t_data *data, char **argv) 
{
    char    *path;

    write(1, "------A------\n", 14);
    path = NULL;
    if (argv[2])
    {
        data->exit_code = 1;
        ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
        return ;
    }
    if (!argv[1]) // si pas d'argument donné, retour à HOME.
    {
        data->exit_code = 0;
        path = ft_strdup(get_env_value(data->env, "HOME"));// must add a space before because the get_env_value function starts the name from name[1] instead of name[0]
    }
    else
        path = ft_strdup(argv[1]);
    if (chdir(path) == -1)
	{
        data->exit_code = 1;
        printf_fd(STDERR_FILENO, "cd: %s: No such file or directory\n", path);
        free(path);
        return ;
	}
    update_env(data->env, "PWD", getcwd(path, 0));
    free(path);
    data->exit_code = 0;
}

void    process_pwd(t_data *data)
{
    char    *path;

    path = NULL;
    path = getcwd(path, 0);
    if (path == NULL)
	{
		data->exit_code = 1;
        return ;
	}
    ft_printf("%s\n", path);
    free(path);
    data->exit_code = 0;
}
