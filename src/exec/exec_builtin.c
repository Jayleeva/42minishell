/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:14:02 by yishan            #+#    #+#             */
/*   Updated: 2025/05/06 15:04:04 by yisho            ###   ########.fr       */
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

void	exec_builtin_child(t_cmd *cmd, t_data *data, t_bool has_next)
{
	if (cmd->outfile < 0 && has_next)
		cmd->outfile = data->pipe_fd[1];
	else
		close(data->pipe_fd[1]);
	close(data->pipe_fd[0]);
	execute_builtin(data, cmd);
	exit(data->exit_code);
}

// t_bool	execute_builtin(t_data *data, t_cmd *cmd)
// {
// 	int	out;

// 	out = -1;
// 	if (cmd->outfile >= 0)
// 	{
// 		out = dup(1);
// 		dup2(cmd->outfile, 1);
// 	}
// 	process_cmd(data, data->cmd);
// 	if (cmd->outfile >= 0)
// 	{
// 		dup2(out, 1);
// 		close (out);
// 	}
// 	return (TRUE);
// }

static t_bool setup_builtin_redirections(t_cmd *cmd, int *saved_stdout, int *saved_stdin, 
                                       int *need_restore_out, int *need_restore_in)
{
    if (cmd->outfile >= 0)
    {
        *saved_stdout = dup(STDOUT_FILENO);
        if (*saved_stdout == -1) {
            perror("minishell: dup");
            return (FALSE);
        }
        if (dup2(cmd->outfile, STDOUT_FILENO) == -1) {
            perror("minishell: dup2");
            close(*saved_stdout);
            return (FALSE);
        }
        *need_restore_out = 1;
    }
    if (cmd->infile >= 0)
    {
        *saved_stdin = dup(STDIN_FILENO);
        if (*saved_stdin == -1) {
            perror("minishell: dup");
            if (*need_restore_out) {
                dup2(*saved_stdout, STDOUT_FILENO);
                close(*saved_stdout);
            }
            return (FALSE);
        }
        if (dup2(cmd->infile, STDIN_FILENO) == -1) {
            perror("minishell: dup2");
            close(*saved_stdin);
            if (*need_restore_out) {
                dup2(*saved_stdout, STDOUT_FILENO);
                close(*saved_stdout);
            }
            return (FALSE);
        }
        *need_restore_in = 1;
    }
    
    return (TRUE);
}

static void	restore_builtin_redirections(int saved_stdout, int saved_stdin,
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
	write(1, "----A----\n", 10);
	int	saved_stdout;
	int	saved_stdin;
	int	need_restore_out;
	int	need_restore_in;

	saved_stdout = -1;
	saved_stdin = -1;
	need_restore_out = 0;
	need_restore_in = 0;
	if (!setup_builtin_redirections(cmd, &saved_stdout, &saved_stdin, &need_restore_out, &need_restore_in))
		return (FALSE);
	write(1, "----B----\n", 10);
	process_cmd(data, cmd);
	write(1, "----C----\n", 10);
	restore_builtin_redirections(saved_stdout, saved_stdin, need_restore_out, need_restore_in);
	return (TRUE);
}
