/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:08:02 by yisho             #+#    #+#             */
/*   Updated: 2025/04/22 10:44:11 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

//Built-in handling (no fork).
//For built-ins, execute directly in the parent process
//Signal management (Ctrl-C behavior).
//Environment variable updates (export, unset).

static t_bool	setup_redirections(t_cmd *cmd, int prev_pipe,
		t_data *data, t_bool has_next)
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) < 0)
			return (FALSE);
		close(cmd->infile);
	}
	else if (prev_pipe != -1)
	{
		if (dup2(prev_pipe, STDIN_FILENO) < 0)
			return (FALSE);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
			return (FALSE);
		close(cmd->outfile);
	}
	else if (has_next)
	{
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
			return (FALSE);
	}
	return (TRUE);
}

/*char **env_to_array(t_env *env_list)
{
    int count = 0;
    t_env *tmp = env_list;
    
    // Count variables
    while (tmp && ++count)
        tmp = tmp->next;
    
    // Allocate array + NULL terminator
    char **env_array = malloc((count + 1) * sizeof(char *));
    if (!env_array)
        return NULL;

    // Convert each entry
    tmp = env_list;
    for (int i = 0; tmp; tmp = tmp->next)
    {
        env_array[i] = malloc(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2);
        if (!env_array[i]) {
            free_array(env_array); // Cleanup if allocation fails
            return NULL;
        }
        ft_strcpy(env_array[i], tmp->key);
        ft_strcat(env_array[i], "=");
        ft_strcat(env_array[i], tmp->value);
        i++;
    }
    env_array[count] = NULL;
    return env_array;
}*/

static void	exit_clean(t_data *data, char **env_array, char *path, int status)
{
	if (data->pipe_fd[1] != -1)
		close(data->pipe_fd[1]);
	if (path)
		free(path);
	if (env_array)
		array_clear(env_array);
	exit(status);
}

/*Make sure data->paths points to the full executable path like /bin/ls.
If paths is an array (from PATH parsing), you need 
to resolve it before calling execve*/
void	child_process(t_data *data, t_cmd *cmd, int prev_pipe, t_bool has_next)
{
	char	*path;
	char	**env_array;

	path = NULL;
	env_array = NULL;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	if (!setup_redirections(cmd, prev_pipe, data, has_next))
		exit_clean(data, env_array, path, EXIT_FAILURE);
	if (is_builtin(cmd->argv[0]))
	{
		execute_builtin(data, cmd);
		exit_clean(data, env_array, path, data->exit_code);
	}
	if (!cmd->argv[0])
		exit_clean(data, env_array, path, EXIT_SUCCESS);
	path = find_cmd_path(data, cmd->argv[0], data->env);
	if (!path)
		exit_clean(data, env_array, path, 127);
	//env_array = env_to_array(data->env);
	//execve(path, cmd->argv, env_array);
}
