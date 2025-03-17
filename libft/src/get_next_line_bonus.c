/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:16:25 by cyglardo          #+#    #+#             */
/*   Updated: 2024/11/28 17:00:03 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_line(int fd, char *stash)
{
	char	*buffer;
	int		read_bytes;
	char	*temp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (free(stash), NULL);
	read_bytes = 1;
	while (read_bytes > 0 && (!*stash || strchr_(stash, '\n') == -1))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buffer), free(stash), NULL);
		else if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		free(temp);
	}
	free(buffer);
	return (stash);
}

static char	*extract_line(char *stash, int eol)
{
	char	*line;

	if (stash[eol] == '\0')
	{
		line = ft_strdup(stash);
		stash = NULL;
		return (line);
	}
	line = ft_substr(stash, 0, eol +1);
	return (line);
}

char	*update_stash(char *stash, int eol)
{
	char	*temp;

	temp = stash;
	stash = ft_substr(stash, eol +1, ft_strlen_(stash) - eol);
	free(temp);
	return (stash);
}

ssize_t	end_of_line(char *s)
{
	ssize_t	eol;

	eol = 0;
	while (s[eol] && s[eol] != '\n')
		eol ++;
	return (eol);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (stash[fd] == NULL)
		stash[fd] = ft_strdup("");
	stash[fd] = read_line(fd, stash[fd]);
	if (!stash[fd] || !*stash[fd])
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	line = extract_line(stash[fd], end_of_line(stash[fd]));
	stash[fd] = update_stash(stash[fd], end_of_line(stash[fd]));
	return (line);
}
