/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_directory.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/04/29 16:44:39 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void    process_cd(t_data *data, char **argv) 
{
    if (argv[2])
    {
        data->exit_code = 1;
        ft_printf("minishell: cd: too many arguments\n");
        return ;
    }
    if (!argv[1]) // si pas d'argument donné, retour à HOME.
    {
        data->exit_code = 0;
        chdir(get_env_value(data->env, " HOME")); // must add a space before because the get_env_value function starts the name from name[1] instead of name[0]
        update_env(data->env, "PWD", get_env_value(data->env, " HOME"));
        return ;
    }
    if (chdir(argv[1]) == -1)
	{
		data->exit_code = 1;
        ft_printf("cd: %s: No such file or directory\n", argv[1]);
        return ;
	}
    update_env(data->env, "PWD", argv[1]);
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
