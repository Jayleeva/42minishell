/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/15 12:44:45 by cyglardo         ###   ########.fr       */
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

void	display_export(t_data *data)
{
	t_env	*current;

	data->exit_code = 0;
	current = data->env;
	while (current)
	{
		if (current->exported == 1)
			ft_printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else if (current->exported == 0)
			ft_printf("declare -x %s\n", current->name);
		current = current->next;
	}
}

int	is_valid(char c)
{
	if (c == '_' || ft_isalpha(c))
		return (1);
	else
		return (0);
}
