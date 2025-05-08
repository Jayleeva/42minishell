/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:25:40 by yishan            #+#    #+#             */
/*   Updated: 2025/05/08 12:23:54 by yisho            ###   ########.fr       */
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


static char	*search_environment(t_env *env, char *var_name, int name_len)
{
	while (env)
	{
		if (!ft_strncmp(env->name, var_name, name_len))
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env, char *name)
{
	return (search_environment(env, &name[1], ft_strlen(name)));
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
