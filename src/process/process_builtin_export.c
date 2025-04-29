/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/04/29 16:46:50 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void	display_export(t_data *data)
{
	t_env	*current;

	data->exit_code = 0;
	current = data->export;
	while (current->next != NULL)
	{
		ft_printf("declare -x %s\n", current->var);
		current = current->next;
	}
	ft_printf("declare -x %s\n", current->var);
}

void	update_var_export(char *var, char *cmd)
{
	if (!ft_strncmp(var, cmd, ft_strlen(cmd))) // si exactement le même input, ne rien faire
		ft_printf("-- no changes in export --\n");
	else // si même var mais pas même value, remplacer value; PAS DE MALLOC
	{
		free(var);
		var = NULL;
		var = ft_strdup(cmd);
		ft_printf("-- has been changed in export -- \n");
	}
}

void	update_export(t_data *data, char *cmd)
{
	t_env	*current;

	current = data->export;
	while (current->next != NULL)
	{
		if (!ft_strncmp(current->var, cmd, ft_strlen(get_name(cmd))))
		{
			update_var_export(current->var, cmd);
			return ;
		}
		else // sinon, finir la liste 
			current = current->next;
	}
	if (!ft_strncmp(current->var, cmd, ft_strlen(get_name(cmd))))
	{
		update_var_export(current->var, cmd);
		return ;
	}
	current->next = (t_env *)malloc(sizeof(t_env)); // malloc pour créer nouvelle var
	if (current->next == NULL)
		return ;
	current->next->var = ft_strdup(cmd); // peut aussi juste assigner cmd mais du coup même pointeur que la liste donc peut pas être free séparément, à voir ce qui est le mieux; si utilise strdup, ajouter protection.
	current->next->next = NULL;
	ft_printf("-- has been added to export -- \n");
}

void	add_empty_export(t_data *data, char *cmd)
{
	char	*temp;

	temp = ft_strjoin(cmd, "\"\"");

	update_export(data, temp);
	free(temp);
}

void	process_export(t_data *data, char **argv)
{
	int		i;

	//i = 0;
	data->exit_code = 0;
    if (!argv[1])
    {
        display_export(data);
        return;
    }
	i = strchri(argv[0], '=');
	if (i == 0)
	{
		ft_printf("minishell: export: `=': not a valid identifier\n");
		return ;
	}
	if (i < 0) //si pas de =, doit être ajouté à la liste d'export mais pas à la liste d'env.
	{
		update_export(data, argv[0]);
		return ;
	}
	if (!argv[0][i +1]) //si = mais pas de valeur, doit être ajouté à la liste d'export avec "" après le =, et ajouté à la liste d'env sans ""; si même nom existe déjà, remplacer, pas créer en plus.
		add_empty_export(data, argv[0]);
	else
		update_export(data, argv[0]);
	add_to_env(data, argv[0], i);
}
