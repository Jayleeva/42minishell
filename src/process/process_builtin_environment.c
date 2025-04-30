/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_environment.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/04/29 17:01:51 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void    process_env(t_data *data, char **argv)
{
	t_env	*current;

	data->exit_code = 0;
	if (argv[1])
	{
		data->exit_code = 1;
		ft_printf("minishell: env: too many arguments\n");
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