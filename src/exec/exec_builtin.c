/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:14:02 by yishan            #+#    #+#             */
/*   Updated: 2025/05/12 12:00:01 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

t_bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if (!ft_strncmp("cd", cmd, 3) || \
		!ft_strncmp("echo", cmd, 5) || \
		!ft_strncmp("pwd", cmd, 4) || \
		!ft_strncmp("export", cmd, 7) || \
		!ft_strncmp("unset", cmd, 6) || \
		!ft_strncmp("env", cmd, 3) || \
		!ft_strncmp("exit", cmd, 5))
		return (TRUE);
	return (FALSE);
}

static t_bool	set_output_red(t_cmd *cmd,
		int *saved_stdout, int *need_restore_out)
{
	if (cmd->outfile < 0)
		return (TRUE);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
		return (FALSE);
	if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
	{
		close(*saved_stdout);
		return (FALSE);
	}
	*need_restore_out = 1;
	return (TRUE);
}

static t_bool	set_input_red(t_cmd *cmd, int *saved_stdin,
			int *need_restore_in)
{
	if (cmd->infile < 0)
		return (TRUE);

	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
		return (FALSE);
	if (dup2(cmd->infile, STDIN_FILENO) == -1)
	{
		close(*saved_stdin);
		return (FALSE);
	}
	*need_restore_in = 1;
	return (TRUE);
}

static void	restore_builtin_red(int saved_stdout, int saved_stdin,
	int need_restore_out, int need_restore_in)
{
	if (need_restore_out)
	{
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
			perror("minishell: dup2 restore");
		close(saved_stdout);
	}
	if (need_restore_in)
	{
		if (dup2(saved_stdin, STDIN_FILENO) == -1)
			perror("minishell: dup2 restore");
		close(saved_stdin);
	}
}

t_bool	execute_builtin(t_data *data, t_cmd *cmd)
{
	int	save_stdout;
	int	save_stdin;
	int	restore_out;
	int	restore_in;

	save_stdout = -1;
	save_stdin = -1;
	restore_out = 0;
	restore_in = 0;
	if (!set_output_red(cmd, &save_stdout, &restore_out))
		return (FALSE);
	if (!set_input_red(cmd, &save_stdin, &restore_in))
	{
		if (restore_out)
		{
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdout);
		}
		return (FALSE);
	}
	process_cmd(data, cmd);
	restore_builtin_red(save_stdout, save_stdin, restore_out, restore_in);
	return (TRUE);
}
