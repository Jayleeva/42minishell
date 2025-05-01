/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:02:25 by yisho             #+#    #+#             */
/*   Updated: 2025/05/01 15:26:29 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

static char	*cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : command not found\n", 2);
	return (NULL);
}

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
		free (paths[i++]);
	free (paths);
}

static char	*join_with_slash(char *path, char *cmd)
{
	char	*full_path;
	char	*tmp;

	if (!path || !cmd)
		return (NULL);
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

static void	init_paths(t_data *data, t_env *env)
{
	char	*path_env;

	path_env = NULL;
	while (env)
	{
		if (ft_strncmp(env->var, "PATH=", 5) == 0)
		{
			path_env = env->var + 5;
			break ;
		}
		env = env->next;
	}
	if (path_env)
		data->paths = ft_split(path_env, ':');
	else
		data->paths = NULL;
}

char	*find_cmd_path(t_data *data, char *cmd, t_env *env)
{
	char	*full_path;
	int		i;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	init_paths(data, env);
	if (!data->paths)
		return (cmd_not_found(cmd));
	i = 0;
	while (data->paths[i])
	{
		full_path = join_with_slash(data->paths[i], cmd);
		if (!full_path)
			break ;
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_paths(data->paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths(data->paths);
	return (cmd_not_found(cmd));
}
