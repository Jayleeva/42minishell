/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:50:13 by yishan            #+#    #+#             */
/*   Updated: 2025/04/17 11:10:31 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

/*Create pipe (pipe(fd) → fd[0] (read), fd[1] (write))
Set cmd1's outfile to fd[1] (write end)
Set cmd2's infile to fd[0] (read end)*/
//HEREDOC does not read from a file; it reads user input from stdin
//until it matches a delimiter. reating a temporary file,
//writing user input to it, and then opening it for reading.
static int	open_file(t_data *data, char *filename, int type)
{
	int	fd;

	fd = -1;
	if (type == INPUT)
		fd = open(filename, O_RDONLY);
	else if (type == HEREDOC)
		fd = here_doc(data, filename);
	else if (type == OUTPUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (type != HEREDOC || fd < 0)
		perror("Error opening file");
	return (fd);
}

static t_bool	process_input_redirect(t_data *data, t_token *token, t_cmd *cmd)
{
	if (token->type == INPUT || token->type == HEREDOC)
	{
		if (!token->next || token->next->type == PIPE
			|| is_redirection(token->next->type))
			return (print_error_token(token, data));
		cmd->infile = open_file(data, token->next->str, token->type);
		if (cmd->infile == -1)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	setup_command_input(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token	*current;

	current = token;
	while (current && current->type != PIPE)
	{
		if (!process_input_redirect(data, current, cmd))
			return (FALSE);
		current = current->next;
	}
	return (TRUE);
}

static t_bool	process_output_redirect(t_data *data,
			t_token *token, t_cmd *cmd)
{
	if (token->type == OUTPUT || token->type == APPEND)
	{
		if (!token->next || token->next->type == PIPE
			|| is_redirection(token->next->type))
			return (print_error_token(token, data));
		cmd->outfile = open_file(data, token->next->str, token->type);
		if (cmd->outfile == -1)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	setup_command_output(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token	*current;

	current = token;
	while (current && current->type != PIPE)
	{
		if (!process_output_redirect(data, current, cmd))
			return (FALSE);
		current = current->next;
	}
	return (TRUE);
}
