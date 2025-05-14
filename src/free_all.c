/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/12 13:46:10 by cyglardo         ###   ########.fr       */
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
		write(1, "-A-\n", 4);
		current = *env;
		if (current->added)
		{
			write(1, "-B-\n", 4);
			current->var = NULL;
			current->name = NULL;
			/*if (current->name || *current->name)
				free(current->name);*/
			free(current->value);
			current->value = NULL;
		}
		free_env(&(current->next));
		free (current);
		*env = NULL;
	}
}
