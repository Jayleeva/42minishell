/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_environment.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/08 13:39:44 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void	process_env(t_data *data, char **argv)
{
	t_env	*current;

	data->exit_code = 0;
	if (argv[1])
	{
		data->exit_code = 1;
		ft_putstr_fd("minishell: env: too many arguments\n", STDERR_FILENO);
		return ;
	}
	current = data->env;
	while (current)
	{
		if (current->exported != 0)
			ft_printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

t_env	*find_var(t_env *head, char *name)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (!ft_strncmp(current->name, name, ft_strlen(name)))
			return (current);
		else
			current = current->next;
	}
	return (NULL);
}

void	update_env(t_env *env, char *name, char *value)
{
	t_env		*current;
	static int	i = 0;
	int			temp;

	current = find_var(env, name);
	if (!ft_strncmp(name, "PWD", 3))
	{
		i ++;
		if (i == 1 && !find_var(env, "OLDPWD"))
			add_new_var(env, "OLDPWD", current->value, 1);
		else
			update_env(env, "OLDPWD", current->value);
	}
	if (!ft_strncmp(name, "SHLVL", 5))
	{
		temp = ft_atoi(value);
		value = ft_itoa(ft_atoi(current->value) + temp);
	}
	current->value = ft_strdup(value);
	free(value);
}
