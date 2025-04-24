/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:25:40 by yishan            #+#    #+#             */
/*   Updated: 2025/04/24 15:56:45 by yisho            ###   ########.fr       */
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

char	*get_env_value(t_env *env, char *name)
{
	t_env	*current;
	int		name_len;
	char	*equal_sign;
	char	*nameeq;

	if (!name)
		return (NULL);
	nameeq = ft_strjoin(&(name[1]), "=");
	if (!nameeq)
		return (NULL);
	name_len = ft_strlen(nameeq);
	current = env;
	while (current)
	{
		if (ft_strncmp(current->var, nameeq, name_len) == 0)
		{
			equal_sign = ft_strchr(current->var, '=');
			if (equal_sign)
			{
				free(nameeq);
				return (ft_strdup(equal_sign + 1));
			}
		}
		current = current->next;
	}
	free(nameeq);
	return (NULL);
}

static char	*search_environment(t_env *env, char *var_name, int name_len)
{
	char	*equal_sign;

	while (env)
	{
		equal_sign = ft_strchr(env->var, '=');
		if (equal_sign && (equal_sign - env->var) == name_len
			&& !ft_strncmp(env->var, var_name, name_len))
		{
			return (equal_sign + 1);
		}
		env = env->next;
	}
	return (NULL);
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
	value = search_environment(data->env, &input[*i + 1], name_len);
	if (value)
	{
		*i += name_len + 1;
		return (1);
	}
	return (0);
}
