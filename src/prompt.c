/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:32:09 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/15 15:03:01 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

int	is_root(t_env *env)
{
	char	*path;

	path = find_var(env, "PWD")->value;
	if (!ft_strncmp(path, "/root", ft_strlen(path)))
		return (1);
	return (0);
}

char	*update_prompt(t_env *env)
{
	char		*buffer;
	char		*prompt;

	prompt = ft_strdup("minishell");
	if (is_root(env))
	{
		buffer = prompt;
		prompt = ft_strjoin(prompt, ":~# ");
		free(buffer);
		return (prompt);
	}
	buffer = prompt;
	prompt = ft_strjoin(prompt, ":");
	free(buffer);
	buffer = prompt;
	prompt = ft_strjoin(prompt, find_var(env, "PWD")->value);
	free(buffer);
	buffer = prompt;
	prompt = ft_strjoin(prompt, "# ");
	free(buffer);
	return (prompt);
}
