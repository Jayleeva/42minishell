/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:58:45 by yishan            #+#    #+#             */
/*   Updated: 2025/05/08 12:25:22 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

static t_bool	handle_line(t_data *data, int fd, char *line, char *delimiter)
{
	if (!line)
	{
		printf_fd(STDERR_FILENO, "Warning: here-document delimited by \
				end-of-file \n(wanted '%c')\n", delimiter);
		return (FALSE);
	}
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
	{
		free(line);
		return (TRUE);
	}
	if (!dollar_handle(&line, data))
	{
		free(line);
		return (FALSE);
	}
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
	free(line);
	return (TRUE);
}

static t_bool	read_heredoc_input(t_data *data, int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = NULL;
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			if (!line)
				handle_line(data, fd, NULL, delimiter);
			else
				free(line);
			break ;
		}
		if (!handle_line(data, fd, line, delimiter))
			return (FALSE);
	}
	return (TRUE);
}

int	here_doc(t_data *data, char *delimiter)
{
	int		fd;
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (-1);
		if (!read_heredoc_input(data, fd, delimiter))
		{
			close(fd);
			unlink(".heredoc.tmp");
			return (-1);
		}
		close(fd);
	}
	else if (pid < 0)
		return (-1);
	waitpid(pid, &status, 0);
	// if (WIFEXITED(status) && WIFSIGNALED(status) != 0)
	// 	return (-1);
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd >= 0)
		unlink(".heredoc.tmp");
	return (fd);
}
