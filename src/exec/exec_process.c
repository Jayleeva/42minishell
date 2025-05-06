/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:08:02 by yisho             #+#    #+#             */
/*   Updated: 2025/05/06 14:45:04 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

static void	add_child_pid(t_data *data, pid_t pid)
{
	data->child_pids = realloc(data->child_pids,
			(data->child_count + 1) * sizeof(pid_t));
	if (!data->child_pids)
	{
		perror("minishell: failed to allocate child PIDs");
		exit(EXIT_FAILURE);
	}
	data->child_pids[data->child_count++] = pid;
}

void	parent_process(t_data *data, pid_t pid, t_cmd *cmd, t_bool has_next)
{
	if (!has_next)
		data->last_pid = pid;
	add_child_pid(data, pid);
	if (has_next)
		close(data->pipe_fd[1]);
	if (cmd->next && cmd->next->infile == -2)
		cmd->next->infile = data->pipe_fd[0];
	else if (has_next)
		close(data->pipe_fd[0]);
}

static t_bool	setup_redirections(t_cmd *cmd, int prev_pipe,
				t_data *data, t_bool has_next)
{
	if (cmd->infile >= 0) //CYCY: != 0; YISHAN: >=0
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1) //CYCY: == -1; YISHAN: < 0
			return (FALSE);
		close(cmd->infile);
	}
	else if (prev_pipe != -1)
	{
		if (dup2(prev_pipe, STDIN_FILENO) == -1) //CYCY: == -1; YISHAN: < 0
			return (FALSE);
		close(prev_pipe);
	}
	if (cmd->outfile >= 0) //CYCY: != 1; YISHAN: >=0
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1) //CYCY: == -1; YISHAN: < 0
			return (FALSE);
		close(cmd->outfile);
	}
	else if (has_next)
	{
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1) //CYCY: == -1; YISHAN: < 0
			return (FALSE);
		close(data->pipe_fd[1]);
	}
	close(data->pipe_fd[0]);
	return (TRUE);
}

void	child_process(t_data *data, t_cmd *cmd, int prev_pipe, t_bool has_next)
{
	char	*path;
	char	**env_array;

	path = NULL;
	env_array = NULL;
	if (is_builtin(cmd->argv[0]))
		exec_builtin_child(cmd, data, has_next);
	if (!setup_redirections(cmd, prev_pipe, data, has_next))
		exit(EXIT_FAILURE);
	execve(path, cmd->argv, env_array);
	if (!resolve_command_path(data, cmd, &path))
		exit(data->exit_code);
	env_array = env_to_array(data->env);
	if (!env_array)
	{
		perror("env_to_array");
		free(path);
		exit(1);
	}
	//update_env(data->env, "SHLVL", "+1");
	execve(path, cmd->argv, env_array);
	perror("execve");
	free(path);
	array_clear(env_array);
	exit(1);
}
