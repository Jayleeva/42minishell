/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:37:31 by yishan            #+#    #+#             */
/*   Updated: 2025/05/01 15:59:31 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

static t_bool	check_if_directory(char *path, char *cmd, t_data *data)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		printf_fd(STDERR_FILENO, "%s: Is a directory\n", cmd);
		/*ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);*/
		data->exit_code = 126;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	resolve_command_path(t_data *data, t_cmd *cmd, char **path)
{
	if (!ft_strchr(cmd->argv[0], '/'))
		*path = find_cmd_path(data, cmd->argv[0], data->env);
	else
		*path = ft_strdup(cmd->argv[0]);
	if (!(*path))
	{
		data->exit_code = 127;
		return (FALSE);
	}
	if (access(*path, X_OK) != 0)
	{
		perror(*path);
		free(*path);
		*path = NULL;
		data->exit_code = 126;
		return (FALSE);
	}
	if (!check_if_directory(*path, cmd->argv[0], data))
	{
		free(*path);
		*path = NULL;
		return (FALSE);
	}
	return (TRUE);
}

void	exec_builtin_child(t_cmd *cmd, t_data *data, t_bool has_next)
{
	if (cmd->outfile < 0 && has_next)
		cmd->outfile = data->pipe_fd[1];
	else
		close(data->pipe_fd[1]);
	close(data->pipe_fd[0]);
	execute_builtin(data, cmd);
	exit(data->exit_code);
}

static size_t	env_lenght(t_env *list)
{
	t_env	*current;
	size_t	i;

	if (list)
	{
		current = list;
		i = 1;
		while (current->next != list && current->next != NULL)
		{
			i++;
			current = current->next;
		}
		return (i);
	}
	return (0);
}

char	**env_to_array(t_env *env)
{
	t_env	*list;
	int		i;
	char	**dst;

	i = 0;
	dst = NULL;
	list = env;
	dst = malloc(sizeof(char *) * (env_lenght(list) + 1));
	if (!dst)
		return (NULL);
	dst[i] = (list->var);
	list = list->next;
	i++;
	while (list != env && list != NULL)
	{
		dst[i] = (list->var);
		list = list->next;
		i++;
	}
	dst[i] = NULL;
	return (dst);
}
