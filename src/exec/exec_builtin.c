/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:14:02 by yishan            #+#    #+#             */
/*   Updated: 2025/04/22 10:30:43 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

t_bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	return (ft_strncmp("cd", cmd, INT_MAX) == 0 || \
			ft_strncmp("echo", cmd, INT_MAX) || \
			ft_strncmp("pwd", cmd, INT_MAX) || \
			ft_strncmp("export", cmd, INT_MAX) || \
			ft_strncmp("unset", cmd, INT_MAX) || \
			ft_strncmp("env", cmd, INT_MAX) || \
			ft_strncmp("exit", cmd, INT_MAX));
}

t_bool	execute_builtin(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	int	out;

	out = -1;
	if (cmd->outfile >= 0)
	{
		out = dup(1);
		dup2(cmd->outfile, 1);
	}
	//executing_built_in(out, data, cmd);
	if (cmd->outfile >= 0)
	{
		dup2(out, 1);
		close (out);
	}
	return (TRUE);
}
