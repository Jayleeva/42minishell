/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:42:06 by yisho             #+#    #+#             */
/*   Updated: 2025/04/10 13:51:26 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

// Fork the process
// call child_process
// If wait for child process fails, exit cleanly
// Call parent_process
void	fork_it_all(t_vars *vars, int ac, char **av, char **enp)
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
