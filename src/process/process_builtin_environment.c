/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_environment.c                      :+:      :+:    :+:   */
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

void    process_env(t_data *data)
{
	t_env	*current;

	data->exit_code = 0;
	current = data->env;
	while (current->next != NULL)
	{
		ft_printf("%s\n", current->var);
		current = current->next;
	}
	ft_printf("%s\n", current->var);
}

void	update_var(char *var, char *cmd, char *name, char *value)
{
	ft_printf("-- already exists -- \n");
	if (value == NULL) // si même var mais value vide, réécrire "var="
	{
		name = ft_strjoin(name, "=");
		free(var);
		var = NULL;
		var = ft_strdup(name);
		ft_printf("-- value empty --\n");
		return ;
	}
	if (!ft_strncmp(var, cmd, ft_strlen(cmd))) // si exactement le même input, ne rien faire
		ft_printf("-- no changes --\n");
	else // si même var mais pas même value, remplacer value; PAS DE MALLOC
	{
		free(var);
		var = NULL;
		var = ft_strdup(cmd);
		ft_printf("-- has been changed -- \n");
	}
}

void	update(t_data *data, char *cmd, char *name, char *value)
{
	t_env	*current;

	current = data->env;
	while (current->next != NULL)
	{
		if (!ft_strncmp(current->var, name, ft_strlen(name)))
		{
			update_var(current->var, cmd, name, value);
			return ;
		}
		else // sinon, finir la liste 
			current = current->next;
	}
	if (!ft_strncmp(current->var, name, ft_strlen(name)))
	{ 
		update_var(current->var, cmd, name, value);
		return ;
	}
	current->next = (t_env *)malloc(sizeof(t_env)); // malloc pour créer nouvelle var
	if (current->next == NULL)
		return ;
	current->next->var = ft_strdup(cmd); // peut aussi juste assigner cmd mais du coup même pointeur que la liste donc peut pas être free séparément, à voir ce qui est le mieux; si utilise strdup, ajouter protection.
	current->next->next = NULL;
	ft_printf("-- has been created -- \n");
}

void	add_to_env(t_data *data, char *cmd, int i)
{
	char	*name;
	char 	*value;

	name = ft_substr(cmd, 0, i);
	if (name == NULL)
		return ;
	value = NULL;
	if (cmd[i +1])
		value = ft_substr(cmd, i + 1, ft_strlen(cmd));
	else //si = mais pas de valeur, doit être ajouté à la liste d'export avec "" après le =, et ajouté à la liste d'env sans ""; si même nom existe déjà, remplacer, pas créer en plus.
		add_empty_export(data, cmd);
	update(data, cmd, name, value);
	free(name);
	free(value);
}

void	process_export(char *cmd, t_data *data)
{
	int		i;

	data->exit_code = 0;
	i = strchri(cmd, '=');
	if (i == 0)
	{
		ft_printf("minishell: export: `=': not a valid identifier\n");
		return ;
	}
	if (i < 0) //si pas de =, doit être ajouté à la liste d'export mais pas à la liste d'env.
	{
		update_export(data, cmd);
		return ;
	}
	if (!cmd[i +1]) //si = mais pas de valeur, doit être ajouté à la liste d'export avec "" après le =, et ajouté à la liste d'env sans ""; si même nom existe déjà, remplacer, pas créer en plus.
		add_empty_export(data, cmd);
	else
		update_export(data, cmd);
	add_to_env(data, cmd, i);
}

void	process_unset(char *cmd, t_data *data)
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