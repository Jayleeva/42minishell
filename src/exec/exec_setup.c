/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:42:06 by yisho             #+#    #+#             */
/*   Updated: 2025/05/02 10:46:27 by yishan           ###   ########.fr       */
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
		*prev_pipe = data->pipe_fd[0];
		close(data->pipe_fd[1]);
	}
}

static void	close_redirections(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->outfile != 1) //CYCY mod.: was >= 0 before;
		{
			close(cmd->outfile);
			cmd->outfile = 1; //CYCY mod.: was = -1 before;
		}
		if (cmd->infile != 0) //CYCY mod.: was >=0 before;
		{
			close(cmd->infile);
			cmd->infile = 0; //CYCY mod.: was = -1 before;
		}
		cmd = cmd->next;
	}
}

static t_bool	wait_for_child(t_data *data)
{
	int		status;

	waitpid(data->last_pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_code = 128 + WTERMSIG(status);
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
	while (current)
	{
		has_next = (current->next != NULL);
		if (has_next && pipe(data->pipe_fd) == -1)
			return (FALSE);
		if (is_builtin(current->argv[0]) && !has_next && prev_pipe == -1)
			return (execute_builtin(data, current));
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
