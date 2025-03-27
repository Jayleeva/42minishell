/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:25:40 by yishan            #+#    #+#             */
/*   Updated: 2025/03/27 10:54:07 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

//$? = last exit code
//*str = "Error: " and buff = "1"
int	handle_special_case(t_data *data, char **str)
{
	char	*buff;
	char	*buff2;

	buff = ft_itoa(data->exit_code);
	if (!buff)
		return (0);
	buff2 = ft_strjoin(*str, buff);
	free(buff);
	free(*str);
	if (!buff2)
		return (0);
	*str = buff2;
	return (1);
}

static int	ft_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

static int	get_name_length(char *var_name, char *env_var)
{
	int	length;
	int	env_name_length;

	length = 0;
	while (var_name[length]
		&& (ft_isalnum(var_name[length]) || var_name[length] == '_'))
	{
		length++;
	}
	env_name_length = ft_search(env_var, '=');
	if (length == env_name_length)
		return (length);
	return (0);
}

//($? = last exit code, $$ = process ID)
int	check_env_variable(char *input, int *i, t_data *data)
{
	t_env	*list_env;
	int		env_list_size;
	int		var_name_length;

	if (input[*i + 1] == '?' || input[*i + 1] == '$')
		return (2);
	list_env = data->env;
	env_list_size = env_lenght(list_env);

	while (env_list_size--)
	{
		var_name_length = get_name_length(&input[*i + 1], list_env->str);
		if (ft_strncmp(list_env->str,
				&input[*i + 1], var_name_length) == 0)
		{
			*i += ft_strlen(list_env->str)
				- ft_strlen(ft_strchr(list_env->str, '=')) + 1;
			return (1);
		}
		list_env = list_env->next;
	}
	return (0);
}
