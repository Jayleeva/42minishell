/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:08:02 by yisho             #+#    #+#             */
/*   Updated: 2025/05/02 10:49:43 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

//TODO
//Signal management (Ctrl-C behavior).update heredoc end with ctrl-c
//Environment variable updates (export, unset).

void	parent_process(t_data *data, pid_t pid, t_cmd *cmd, t_bool has_next)
{
	if (!has_next)
		data->last_pid = pid;
	if (cmd->infile >= 0)
	{
		//fprintf(stderr, "[parent_process] Closing cmd->infile = %d\n", cmd->infile);
		close(cmd->infile);
	}
	//fprintf(stderr, "[parent_process] Closing pipe_fd[1] = %d\n", data->pipe_fd[1]);
	close(data->pipe_fd[1]);
}

static t_bool	setup_redirections(t_cmd *cmd, int prev_pipe,
				t_data *data, t_bool has_next)
{
	if (cmd->infile >= 0) //CYCY: != 0; YISHAN: >=0
	{
		if (dup2(cmd->infile, STDIN_FILENO) < 0)
			return (FALSE);
		close(cmd->infile);
	}
	else if (prev_pipe == -1)
	{
		if (dup2(prev_pipe, STDIN_FILENO) < 0)
			return (FALSE);
		close(prev_pipe);
	}
	if (cmd->outfile >= 0)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
			return (FALSE);
		close(cmd->outfile);
	}
	else if (has_next)
	{
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
			return (FALSE);
		close(data->pipe_fd[1]);
	}
	return (TRUE);
}

void	child_process(t_data *data, t_cmd *cmd, int prev_pipe, t_bool has_next)
{
	char	*path;
	char	**env_array;

	path = NULL;
	env_array = NULL;
	/*if (is_builtin(cmd->argv[0]))
		exec_builtin_child(cmd, data, has_next);*/
	if (!setup_redirections(cmd, prev_pipe, data, has_next))
		exit(EXIT_FAILURE);
	if (!resolve_command_path(data, cmd, &path))
		exit(data->exit_code);
	env_array = env_to_array(data->env);
	if (!env_array)
	{
		perror("env_to_array");
		free(path);
		exit(1);
	}
	execve(path, cmd->argv, env_array);
	perror("execve");
	free(path);
	array_clear(env_array);
	exit(1);
}
