/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:42:06 by yisho             #+#    #+#             */
/*   Updated: 2025/05/15 10:25:53 by cyglardo         ###   ########.fr       */
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
		if (data->pipe_fd[1] != -1) //added this, doesn't solve it
			close(data->pipe_fd[1]);
		*prev_pipe = data->pipe_fd[0];
	}
	else 				// tried to comment it, doesn't solve it
		*prev_pipe = -1; // tried to modify this, doesn't solve it 
}

static t_bool	wait_for_child(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->child_count)
	{
		if (waitpid(data->child_pids[i], &status, 0) < 0)
		{
			perror("minishell: waitpid");
			continue ;
		}
		if (data->child_pids[i] == data->last_pid)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					printf_fd(STDERR_FILENO, "Quit (core dumped)\n");
				data->exit_code = 128 + WTERMSIG(status);
			}
		}
		i++;
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
static t_bool	execute_pipeline_commands(t_data *data, int *prev_pipe)
{
	t_cmd	*current;
	t_bool	has_next;

	current = data->cmd;
	while (current)
	{
		has_next = (current->next != NULL);
		if (!current->argv || !current->argv[0])
		{
			current = current->next;
			continue ;
		}
		if (has_next && pipe(data->pipe_fd) == -1)
			return (FALSE);
		if (is_builtin(current->argv[0]) && !has_next)
			return (execute_builtin(data, current));
		if (!execute_cmd(data, current, *prev_pipe, has_next))
			return (FALSE);
		cleanup_pipes(data, prev_pipe, has_next);
		current = current->next;
		if (!current)
			break ;
	}
	return (TRUE);
}

t_bool	execute_pipeline(t_data *data)
{
	int		prev_pipe;
	t_bool	result;

	prev_pipe = -1; // when modified, same warning + error (if set to 1: "standard output : Bad file decriptor". if set to 0: "-: Bad file descriptor")
	if (!execute_pipeline_commands(data, &prev_pipe))
		return (FALSE);
	result = wait_for_child(data);
	close_redirections(data);
	return (result);
}
