/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/08 13:50:20 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

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
}

void	update_value(t_env *env, char *var, char *value, int to_export)
{
	t_env	*current;

	current = env;
	if (to_export == 1)
	{
		current->var = var;
		current->value = value;
		current->exported = 1;
	}
	return ;
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
		if (!ft_strncmp(current->name, name, ft_strlen(name)))
			update_value(current, var, value, to_export);
		current = current->next;
	}
	if (!ft_strncmp(current->name, name, ft_strlen(name)))
		update_value(current, var, value, to_export);
	else
		add_new_var(current, name, value, to_export);
}

void	export(t_env *env, char *var, int i)
{
	int		to_export;
	char	*name;
	char	*value;

	name = get_name(var);
	if (i < 0)
	{
		to_export = 0;
		value = ft_strdup("");
	}
	else
	{
		to_export = 1;
		value = ft_substr(var, i + 1, ft_strlen(var));
	}
	update_export(env, name, value, to_export);
}

void	process_export(t_data *data, char **argv)
{
	int	i;
	int	j;

	data->exit_code = 0;
	if (!argv[1])
	{
		display_export(data);
		return ;
	}
	i = 1;
	while (argv[i])
	{
		j = strchri(argv[i], '=');
		if (j == 0)
			printf_fd(STDERR_FILENO,
				"minishell: export: `=': not a valid identifier\n");
		else
			export(data->env, argv[i], j);
		i ++;
	}
}
