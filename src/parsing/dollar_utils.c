/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:25:40 by yishan            #+#    #+#             */
/*   Updated: 2025/05/12 11:32:22 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

char	*extract_var_name(char *input, int length)
{
	char	*name;
	int		i;

	name = malloc(sizeof(char) * (length + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (input[i] && i < length)
	{
		name[i] = input[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}


static char	*search_environment(t_env *env, char *var_name)
{
	char	*value;

	value = find_var(env, var_name)->value;
	return (value);
	/*while (env)
	{
		if (!ft_strncmp(env->name, var_name, name_len))
		{
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (NULL);*/
}

char	*get_env_value(t_env *env, char *name)
{
	return (search_environment(env, &name[1]));
}

//Extracts and validates variable name length
static int	get_var_name_length(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	return (i);
}

int	check_env_variable(char *input, int *i, t_data *data)
{
	int		name_len;
	char	*value;

	if (input[*i + 1] == '?' || input[*i + 1] == '$')
		return (2);
	name_len = get_var_name_length(&input[*i + 1]);
	if (!name_len)
		return (0);
	value = search_environment(data->env, &input[*i + 1]);
	if (value)
	{
		*i += name_len + 1;
		//free(value);
		return (1);
	}
	return (0);
}