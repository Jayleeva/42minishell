/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/01 12:06:14 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

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

void	add_new_var(t_env *env, char *name, char *value, int to_export)
{
	t_env	*current;

	current = env;
	while (current->next)
		current = current->next;
	current->next = (t_env *)malloc(sizeof(t_env));
	if (current->next == NULL)
		return ;
	current->next->var = ft_strjoin(name, "=");
	current->next->var = ft_strjoin(current->next->var, value);
	current->next->name = name;
	current->next->value = value;
	current->next->exported = to_export;
	current->next->next = NULL;
	//printf("-- has been added -- \n");
}

void	update_value(t_env *env, char *var, char *value, int to_export)
{
	t_env	*current;

	current = env;
	if (to_export == 1) //si l'argument reçu contient un égal, doit être exporté (sera display par export et par env)
	{
		current->var = var;
		current->value = value;
		current->exported = 1;
		//printf("-- has been modified-- \n");
	}
	/*else
		printf("-- nothing changed -- \n");*/
	return; //if (!exported), return; // si l'argument reçu ne contient pas d'égal, rien ne change: ne rien faire
}

void	update_export(t_env *env, char *name, char *value, int to_export)
{
	t_env	*current;
	char	*var;

	var = ft_strjoin(name, "=");
	var = ft_strjoin(var, value);
	
	current = env;
	while (current->next)
	{
		if (!ft_strncmp(current->name, name, ft_strlen(name))) // si la var existe déjà (même nom)
			update_value(current, var, value, to_export);
		current = current->next;
	}
	if (!ft_strncmp(current->name, name, ft_strlen(name))) // si la var existe déjà (même nom)
		update_value(current, var, value, to_export);
	else
		add_new_var(current, name, value, to_export); // si n'existe pas déjà, la créer.
}

void	export(t_env *env, char *var, int i)
{
	int		to_export;
	char	*name;
	char	*value;

	name = get_name(var);
	if (i < 0) //si pas de =, doit être ajouté à la liste d'export mais pas display par env.
	{
		to_export = 0;
		value = ft_strdup("");
	}
	else  //si =, doit être ajoutée à la liste d'export et display par new.
	{
		to_export = 1;
		value = ft_substr(var, i + 1, ft_strlen(var));
	}
	update_export(env, name, value, to_export);
}

void	process_export(t_data *data, char **argv)
{
	int		i;

	data->exit_code = 0;
    if (!argv[1]) //si pas d'argument, display la liste
    {
        display_export(data);
        return;
    }
	//while () tant qu'il y a des trucs à exporter!! voir plus tard
	i = strchri(argv[1], '=');
	if (i == 0) // si nom commence par =, pas valable
	{
		ft_printf("minishell: export: `=': not a valid identifier\n");
		return ;
	}
	export(data->env, argv[1], i);
}
