/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:58:45 by yishan            #+#    #+#             */
/*   Updated: 2025/04/09 22:24:08 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

/*static bool	read_heredoc_input(t_data *data, int fd, char *delimiter)
{
	char	*line;

	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			print_error("warning: here-document delimited by end-of-file ");
			print_error("(wanted '");
			print_error(delimiter);
			print_error("')\n");
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (!replace_dollar(&line, data))
		{
			free(line);
			//free_all(data, ERR_MALLOC, EXT_MALLOC);
			return (false);
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	return (true);
}*/

int	here_doc(t_data *data, char *delimiter)
{
	int	fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	/*if (!read_heredoc_input(data, fd, delimiter))
	{
		close(fd);
		unlink(".heredoc.tmp");
		return (-1);
	}
	close(fd)*/;

	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd >= 0)
		unlink(".heredoc.tmp");
	return (fd);
}
