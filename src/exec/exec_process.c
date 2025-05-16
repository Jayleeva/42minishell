/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:08:02 by yisho             #+#    #+#             */
/*   Updated: 2025/05/15 10:35:29 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void	close_redirections(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->outfile >= 0)
		{
			close(cmd->outfile);
			cmd->outfile = -1;
		}
		if (cmd->infile >= 0)
		{
			close(cmd->infile);
			cmd->infile = -1;
		}
		cmd = cmd->next;
	}
	if (data->child_pids)
	{
		free(data->child_pids);
		data->child_pids = NULL;
	}
	data->child_count = 0;
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
	if (!setup_input_redirection(cmd, prev_pipe))
		return (FALSE);
	if (!setup_output_redirection(cmd, data, has_next))
		return (FALSE);
	return (TRUE);
}

static void	execute_external_command(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	**env_array;

	path = NULL;
	env_array = NULL;
	if (!resolve_command_path(data, cmd, &path))
		ft_exit(data, data->exit_code);
	update_env(data->env, "SHLVL", "+1");
	env_array = env_to_array(data->env);
	if (!env_array)
	{
		perror("env_to_array");
		free(path);
		ft_exit(data, 1);
	}
	execve(path, cmd->argv, env_array);
	perror("execve");
	free(path);
	array_clear(env_array);
	ft_exit(data, 1);
}

void	child_process(t_data *data, t_cmd *cmd, int prev_pipe, t_bool has_next)
{
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin_child(cmd, data, has_next);
		ft_exit(data, 0);
	}
	if (!setup_redirections(cmd, prev_pipe, data, has_next))
		ft_exit(data, 1);
	execute_external_command(data, cmd);
}
