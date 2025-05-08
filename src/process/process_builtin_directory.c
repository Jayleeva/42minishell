/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_directory.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/08 14:38:31 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void	process_cd(t_data *data, char **argv)
{
	char	*path;

	path = NULL;
	if (argv[2])
	{
		data->exit_code = 1;
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return ;
	}
	if (!argv[1])
	{
		data->exit_code = 0;
		chdir(find_var(data->env, "HOME")->value);
		update_env(data->env, "PWD", find_var(data->env, "HOME")->value);
		return ;
	}
	if (chdir(argv[1]) == -1)
	{
		data->exit_code = 1;
		printf_fd(STDERR_FILENO, "cd: %s: No such file or directory\n", argv[1]);
		return ;
	}
	update_env(data->env, "PWD", getcwd(path, 0));
	free(path);
	data->exit_code = 0;
}

void	process_pwd(t_data *data)
{
	char	*path;

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
