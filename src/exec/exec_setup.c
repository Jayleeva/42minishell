/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:42:06 by yisho             #+#    #+#             */
/*   Updated: 2025/04/24 13:47:39 by yisho            ###   ########.fr       */
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

static void	close_redirections(t_data *data)
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

static t_bool	execute_cmd(t_data *data, t_cmd *cmd,
		int prev_pipe, t_bool has_next)
{
	pid_t	pid;

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

//pipe_fd[READ], pipe_fd[WRITE]
t_bool	execute_pipeline(t_data *data)
{
	t_cmd	*current;
	t_bool	has_next;
	t_bool	result;
	int		prev_pipe;

	current = data->cmd;
	prev_pipe = -1;
	/*if (current && current->skip_cmd == FALSE && current->next == current
		&& current->argv[0] && is_builtin(current->argv[0]))
		return (execute_builtin(data, current));*/
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
	result = wait_for_child(data);
	close_redirections(data);
	return (result);
}
