/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/15 10:09:17 by cyglardo         ###   ########.fr       */
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
	//current->next->name = ft_strdup(name);
	current->next->name = name;
	current->next->value = ft_strdup(value);
	current->next->exported = to_export;
	current->next->added = 1;
	current->next->next = NULL;
}

void	update_value(t_env *env, char *var, char *value, int to_export)
{
	t_env	*current;
	char	*buffer;

	current = env;
	if (to_export == 1)
	{
		current->var = var;
		buffer = current->value;
		current->value = ft_strdup(value);
		free(buffer);
		current->exported = 1;
	}
	return ;
}

void	update_export(t_env *env, char *name, char *value, int to_export)
{
	t_env	*current;
	char	*var;
	char	*temp;

	var = ft_strjoin(name, "=");
	temp = var;
	var = ft_strjoin(var, value);
	free(temp);
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
	free(var);
}

void	export(t_env *env, char *var, int i)
{
	int		to_export;
	char	*name;
	char	*value;

	name = NULL;
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
	free(name);
	free(value);
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
		if (j == 0 || !is_valid(argv[i][0]))
			printf_fd(STDERR_FILENO,
				"minishell: export: `%c': not a valid identifier\n", argv[i][0]);
		else
			export(data->env, argv[i], j);
		i ++;
	}
}
