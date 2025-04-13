/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:42:06 by yisho             #+#    #+#             */
/*   Updated: 2025/04/12 13:36:22 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

// Fork the process
// call child_process
// If wait for child process fails, exit cleanly
// Call parent_process
void	fork_it_all(t_env *vars, int ac, char **av, char **enp)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		vars->pid = fork();
		if (vars->pid < 0)
			clean_exit(vars, "Fork error", 2, EXIT_FAILURE);
		if (vars->full_cmd)
		{
			free(vars->full_cmd);
			vars->full_cmd = NULL;
		}
		free_cmds(vars, 0);
		child_process(vars, av, enp, 2);
		i++;
	}
	if (wait(NULL) < 0)
		clean_exit(vars, "Wait error", 2, EXIT_FAILURE);
	parent_process(vars, ac, av, enp);
}

// pipe_fd[READ], pipe_fd[WRITE]
t_bool	execute(t_data *data)
{
	t_cmd	*current;

	current = data->cmd;
	if (current && current->skip_cmd == FALSE
		&& current->next == current && is_builtin(current->argv[0]))
		return (execute_builtin(data, current));
	while (current != NULL)
	{
		if (pipe(data->pipe_fd) == -1)
			return (FALSE);
		if (!execute_cmd(data, current))
			return (FALSE);
		current = current->next;
		if (current == NULL)
		{
			wait_all(data);
			break ;
		}
	}
	return (TRUE);
}
