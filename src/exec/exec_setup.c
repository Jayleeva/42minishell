/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:42:06 by yisho             #+#    #+#             */
/*   Updated: 2025/04/18 18:52:55 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

static void	cleanup_pipes(t_data *data, int *prev_pipe, t_bool has_next)
{
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (has_next)
	{
		*prev_pipe = data->pipe_fd[0];
		close(data->pipe_fd[1]);
	}
	else
	{
		close(data->pipe_fd[0]);
		*prev_pipe = -1;
	}
}

static t_bool	wait_for_child(t_data *data)
{
	int		status;
	pid_t	pid;

	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (pid == data->last_pid)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = 128 + WTERMSIG(status);
		}
	}
	return (TRUE);
}

void	parent_process(t_data *data, pid_t pid, t_cmd *cmd, t_bool has_next)
{
	if (!has_next)
		data->last_pid = pid;
	close(data->pipe_fd[1]);
	if (cmd->next && cmd->next->infile == -2)
		cmd->next->infile = data->pipe_fd[0];
	else
		close(data->pipe_fd[0]);
}

static t_bool	execute_cmd(t_data *data, t_cmd *cmd,
		int prev_pipe, t_bool has_next)
{
	pid_t	pid;
	t_bool	is_single_builtin;

	if (cmd && cmd->skip_cmd == FALSE)
	{
		is_single_builtin = (cmd->next == cmd);
		if (is_single_builtin && is_builtin(cmd->argv[0]))
			return (execute_builtin(data, cmd));
	}
	pid = fork();
	if (pid < 0)
	{
		perror ("minishell: fork");
		return (FALSE);
	}
	if (pid == 0)
		child_process(data, cmd, prev_pipe, has_next);
	else
		parent_process(data, pid, cmd, has_next);
	return (TRUE);
}

//1. Create pipe
//2. Execute current command
//3. Cleanup and prepare for next
//pipe_fd[READ], pipe_fd[WRITE]
t_bool	execute_pipeline(t_data *data)
{
	t_cmd	*current;
	t_bool	has_next;
	int		prev_pipe;

	current = data->cmd;
	prev_pipe = -1;
	while (current)
	{
		has_next = (current->next != NULL);
		if (has_next && pipe(data->pipe_fd) == -1)
			return (FALSE);
		if (!execute_cmd(data, current, prev_pipe, has_next))
			return (FALSE);
		cleanup_pipes(data, &prev_pipe, has_next);
		current = current->next;
		if (!current)
			break ;
	}
	return (wait_for_child(data));
}
