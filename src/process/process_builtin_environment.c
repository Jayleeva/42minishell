/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/27 16:54:56 by cyglardo         ###   ########.fr       */
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
		return ;
	}
}

void	update(t_data *data, char *cmd, char *name, char *value)
{
	t_env	*current;

	current = data->env;
	while (current->next != NULL)
	{
		if (!ft_strncmp(current->var, name, ft_strlen(name))) 
			update_var(current->var, cmd, name, value);
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

void	process_export(char *cmd, t_data *data) //ne marche pas tout de suite, doit faire 2 fois avant que env l'affiche : garde chaque itération en mémoire somehow mais ne l'affiche que après 2 itérations...
{

	char	*name;
	char 	*value;
	int		i;

	data->exit_code = 0;
	cmd = ft_substr(cmd, 7, ft_strlen(cmd));  //ADAPT ONCE TOKENS ARE WORKING AND INTEGRATED
	if (cmd == NULL)
		return ;
	i = strchri(cmd, '=');
	if (i < 0)
		return ;
	name = ft_substr(cmd, 0, i);
	if (name == NULL)
		return ;
	value = NULL;
	if (cmd[i +1])
		value = ft_substr(cmd, i + 1, ft_strlen(cmd));
	update(data, cmd, name, value);
	free(cmd);
	free(name);
	free(value);
}

void	process_unset(char *cmd, t_data *data)
{
	t_env	*current;

	cmd = ft_substr(cmd, 6, ft_strlen(cmd));  //ADAPT ONCE TOKENS ARE WORKING AND INTEGRATED
	if (cmd == NULL)
	{
		data->exit_code = 1;
		return ;
	}
	current = data->env;
	while (current->next->next != NULL)
	{
		if (!ft_strncmp(current->next->var, cmd, strchri(current->next->var, '=')))
			break;
		current = current->next;
	}
	current->next = current->next->next;
	//free? what?
}
