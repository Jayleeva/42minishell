/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/04/14 12:50:03 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

char	*get_name(char *cmd)
{
	int		i;
	char	*name;

	name = NULL;
	i = strchri(cmd, '=');
	if (i > 0)
		name = ft_substr(cmd, 0, i);
	else if (i == -1)
		name = ft_strdup(cmd);
	return (name);
}

void	unset_export(char *cmd, t_data *data)
{
	t_env	*current;
	t_env	*prev;

	current = data->export;
	while (current && ft_strncmp(current->var, cmd, ft_strlen(get_name(cmd))))
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	prev->next = current->next;
	free(current);
}

void	unset_env(char *cmd, t_data *data)
{
	t_env	*current;
	t_env	*prev;

	current = data->env;
	while (current && ft_strncmp(current->var, cmd, strchri(current->var, '=')))
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	prev->next = current->next;
	free(current);
}

void	process_unset(char *cmd, t_data *data)
{
    unset_env(cmd, data);
    unset_export(cmd, data);
}