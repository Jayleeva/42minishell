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
		ft_printf("%s\n", current->vartest);
		current = current->next;
	}
}

void	process_export(char *cmd, t_data *data) //ne marche pas tout de suite, doit faire 2 fois avant que env l'affiche : garde chaque itération en mémoire somehow mais ne l'affiche que après 2 itérations...
{
	t_env	*current;
	char	*var;

	cmd = ft_substr(cmd, 7, ft_strlen(cmd));  //ADAPT ONCE TOKENS ARE WORKING AND INTEGRATED
	if (cmd == NULL)
	{
		data->exit_code = 1;
		return ;
	}
	var = ft_substr(cmd, 0, strchri(cmd, '='));
	if (var == NULL)
		return ;
	current = data->env;
	while (current->next != NULL)
	{
		if (!ft_strncmp(current->vartest, cmd, ft_strlen(cmd)))
			return ;
		else
			ft_printf("%s\n", var);
		current = current->next;
	}
	current->next = (t_env *)malloc(sizeof(t_env));
	if (current->next == NULL)
		return ;
	current->next->vartest = ft_strdup(cmd); // peut aussi juste assigner cmd mais du coup même pointeur que la liste donc peut pas être free séparément, à voir ce qui est le mieux; si utilise strdup, ajouter protection.
	current->next->next = NULL;
	free(cmd);
	//ft_printf("%s\n", current->next->vartest);
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
		if (!ft_strncmp(current->next->vartest, cmd, strchri(current->next->vartest, '=')))
			break;
		current = current->next;
	}
	//ft_printf("to delete : %s\n", current->next->vartest);
	current->next = current->next->next;
	//free? what?
}
