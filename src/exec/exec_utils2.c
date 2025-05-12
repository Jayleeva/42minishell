/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:02:22 by yisho             #+#    #+#             */
/*   Updated: 2025/05/12 14:47:03 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

t_bool	setup_input_redirection(t_cmd *cmd, int prev_pipe)
{
	if (cmd->infile >= 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (FALSE);
		close(cmd->infile);
	}
	else if (prev_pipe != -1)
	{
		if (dup2(prev_pipe, STDIN_FILENO) == -1)
			return (FALSE);
		close(prev_pipe);
	}
	return (TRUE);
}

t_bool	setup_output_redirection(t_cmd *cmd, t_data *data, t_bool has_next)
{
	if (cmd->outfile >= 0)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			return (FALSE);
		close(cmd->outfile);
	}
	else if (has_next)
	{
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
			return (FALSE);
		close(data->pipe_fd[1]);
	}
	close(data->pipe_fd[0]);
	return (TRUE);
}

void	add_child_pid(t_data *data, pid_t pid)
{
	pid_t	*new_pids;

	new_pids = ft_realloc(data->child_pids,
			data->child_count * sizeof(pid_t),
			(data->child_count + 1) * sizeof(pid_t));
	if (!new_pids)
	{
		perror("minishell: failed to allocate child PIDs");
		exit(EXIT_FAILURE);
	}
	data->child_pids = new_pids;
	data->child_pids[data->child_count++] = pid;
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}
