/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:08:02 by yisho             #+#    #+#             */
/*   Updated: 2025/04/23 18:43:51 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

//Built-in handling (no fork).
//For built-ins, execute directly in the parent process
//Signal management (Ctrl-C behavior).
//Environment variable updates (export, unset).

void	parent_process(t_data *data, pid_t pid, t_cmd *cmd, t_bool has_next)
{
	if (!has_next)
		data->last_pid = pid;
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->infile == -2)
		cmd->infile = data->pipe_fd[0];
	close(data->pipe_fd[1]);
	if (cmd->next && cmd->next->infile == -2)
		cmd->next->infile = data->pipe_fd[0];
	else
		close(data->pipe_fd[0]);
}

/*static t_bool	setup_redirections(t_cmd *cmd, int prev_pipe,
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
		close(prev_pipe);
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
		close(data->pipe_fd[1]);
	}
	return (TRUE);
}*/



/*Change the environne;ent with the good one and heredoc end with ctrl-c*/
void	child_process(t_data *data, t_cmd *cmd, int prev_pipe, t_bool has_next)
{
	char	*path;
	// char	**env_array;
	extern char **environ;

	path = NULL;
	// env_array = NULL;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	(void)prev_pipe;
	(void)has_next;

	// if (!setup_redirections(cmd, prev_pipe, data, has_next))
	// 	exit_clean(data, env_array, path, EXIT_FAILURE);
	path = find_cmd_path(data, cmd->argv[0], environ);
	// if (!path)
	// 	exit_clean(data, env_array, path, 127);
	// env_array = env_to_array(data->env);
	execve(path, cmd->argv, environ);
}

/*void	child_process(t_data *data, t_cmd *cmd, int prev_pipe, t_bool has_next)
{
	char	*path;
	char	**env_array;

	path = NULL;
	env_array = NULL;
	if (cmd->skip_cmd)
		data->exit_code = 1;
	else if (is_builtin(cmd->argv[0]))
		exec_builtin_chil(cmd, data, has_next);
	if (!resolve_command_path(data, cmd, &path))
		exit(data->exit_code);
	if (!setup_redirections(cmd, prev_pipe, data, has_next))
		exit(EXIT_FAILURE);
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
	clear_array(env_array);
	exit(1);
}*/
