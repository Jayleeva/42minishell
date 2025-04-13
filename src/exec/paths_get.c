/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:02:25 by yisho             #+#    #+#             */
/*   Updated: 2025/04/13 16:31:47 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

static char	*cmd_not_found(char *sample)
{
	ft_putstr_fd(sample, 2);
	ft_putstr_fd(" : command not found\n", 2);
	return (NULL);
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

char	*find_cmd_path(t_data *data, char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || !env || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = NULL;
	while (env && !path_env)
	{
		if (ft_strncmp(env->vartest, "PATH=", 5) == 0)
			path_env = env->vartest + 5;
		env = env->next;
	}
	if (!path_env)
		return (cmd_not_found(cmd));
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = join_with_slash(paths[i], cmd);
		if (!full_path)
			break ;
		if (access(full_path, F_OK | X_OK) == 0)
		{
			array_clear(paths);
			return (full_path);
		}
		free(full_path);
	}
	array_clear(paths);
	return (cmd_not_found(cmd));
}
