/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:02:25 by yisho             #+#    #+#             */
/*   Updated: 2025/04/10 14:18:28 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

// Add a / at the end of each path, If it fails, exit cleanly
// Free the old path and assign the new one

static void	add_slash(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->paths[i])
	{
		tmp = ft_strjoin(data->paths[i], "/");
		if (!tmp)
			clean_exit(data, "Malloc error adding trailing slash", 2, 1);
		free(data->paths[i]);
		data->paths[i] = tmp;
		i++;
	}
}

void	get_paths(char **enp, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (enp[i])
	{
		if (ft_strncmp(enp[i], "PATH=", 5) == 0)
		{
			tmp = ft_strtrim(enp[i], "PATH=");
			if (!tmp)
				exit_msg("Error trimming PATH", 2, EXIT_FAILURE);
			data->paths = ft_split(tmp, ':');
			free(tmp);
		}
		i++;
	}
	if (!data->paths)
		exit_msg("Error finding paths", 2, EXIT_FAILURE);
	add_slash(data);
}
