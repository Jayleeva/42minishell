/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/08 13:44:06 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void	free_env(t_env **env)
{
	t_env	*current;

	if (env && *env)
	{
		current = *env;
		if (current->var)
		{
			current->var = NULL;
			free(current->name);
			current->name = NULL;
			free(current->value);
			current->value = NULL;
		}
		free_env(&(current->next));
		free (current);
		*env = NULL;
	}
}