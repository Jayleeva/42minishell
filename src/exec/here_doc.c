/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:58:45 by yishan            #+#    #+#             */
/*   Updated: 2025/05/15 10:42:17 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

static t_bool	handle_line(t_data *data, int fd, char *line, char *delimiter)
{
	if (!line)
	{
		ft_printf("warning: here-document delimited by end-of-file ");
		ft_printf("(wanted '");
		ft_printf(delimiter);
		ft_printf("')\n");
		return (FALSE);
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

/*static void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	exit(130);
}*/

static void	heredoc_child(t_data *data, char *delimiter)
{
	int	fd;

	//signal(SIGINT, handle_heredoc_sigint);
	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		ft_exit(data, 1);
	if (!read_heredoc_input(data, fd, delimiter))
	{
		close(fd);
		unlink(".heredoc.tmp");
		ft_exit(data, 1);
	}
	close(fd);
	ft_exit(data, 0);
}

int	here_doc(t_data *data, char *delimiter)
{
	int		fd;
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < -1)
		return (-1);
	if (pid == 0)
		heredoc_child(data, delimiter);
	else if (pid < 0)
		return (-1);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (-1);
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd >= 0)
		unlink(".heredoc.tmp");
	return (fd);
}
