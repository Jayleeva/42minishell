/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/12 11:39:50 by cyglardo         ###   ########.fr       */
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
	//free(s);
	return (name);
}

void	free_env_node(t_env *current)
{
	if (current->added)
	{
		write(1, "--A--\n", 6);
		free(current->value);
	}
	//free(current->name);
	current->name = NULL;
	current->var = NULL;
}

void	save_list(t_env	**head, t_env *current)
{
	t_env	*temp;

	if (current->next)
	{
		temp = *head;
		*head = temp->next;
		free_env_node(temp);
		free(temp);
	}
	else
		head = NULL;
}

t_env	*unset_env(t_env **head, char *name)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = *head;
	if (!ft_strncmp(current->name, name, ft_strlen(name)))
	{
		save_list(head, current);
		return (*head);
	}
	while (current && ft_strncmp(current->name, name, ft_strlen(name)))
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = current->next;
		free_env_node(current);
		free(current);
	}
	return (*head);
}

void	process_unset(t_data *data, char **argv)
{
	char	*name;
	t_env	*head;
	int		i;

	name = NULL;
	data->exit_code = 0;
	if (!argv[1])
		return ;
	i = 1;
	while (argv[i])
	{
		name = get_name(argv[i]);
		if (name)
		{
			head = data->env;
			data->env = unset_env(&head, name);
		}
		free(name);
		i ++;
	}
}
