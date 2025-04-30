/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/04/29 16:48:20 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

char	*get_name(char *s)
{
	int		i;
	char	*name;

	name = NULL;
	i = strchri(s, '=');
	if (i > 0)
		name = ft_substr(s, 0, i);
	else if (i == -1)
		name = ft_strdup(s);
	return (name);
}

void	unset_env(t_env *env, char *name)
{
	t_env	*current;
	t_env	*prev;

	current = env;
	while (current && ft_strncmp(current->name, name, ft_strlen(name)))
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	prev->next = current->next;
	free(current);
}

void	process_unset(t_data *data, char **argv)
{
	char	*name;
	data->exit_code = 0;
    if (!argv[1])
	{
		write(1, "HEY\n", 4);
        return ;
	}
	name = get_name(argv[1]);
    unset_env(data->env, name);
}