/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:25:40 by yishan            #+#    #+#             */
/*   Updated: 2025/05/01 15:36:14 by yisho            ###   ########.fr       */
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
	t_env	*var;

	var = find_var(env, name);
	if (!var)
		return (NULL);
	else
		return (var->value);
}

int	check_env_variable(char *input, int *i, t_data *data)
{
	if (input[*i + 1] == '?' || input[*i + 1] == '$')
		return (2);
	
	if (!find_var(data->env, input))
		return (0);
	else
		return (1);
}