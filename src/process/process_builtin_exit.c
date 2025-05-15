/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/15 10:33:50 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../inc/linked_list.h"
#include "../../libft/inc/libft.h"

void	ft_exit(t_data *data, int exit_code)
{
	(void)data;
	//free_env(&data->env);
	rl_clear_history();
	exit(exit_code);
}

int	isnum(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i ++;
	}
	return (1);
}

void	bad_exit(t_data *data, char *arg)
{
	ft_printf("exit\n");
	printf_fd(STDERR_FILENO,
		"minishell: exit: %s: numeric argument required\n", arg);
	data->exit_code = 2;
	ft_exit(data, 2);
}

void	process_exit(t_data *data, char **argv)
{
	data->exit_code = 0;
	if (argv[1])
	{
		if (isnum(argv[1]))
		{
			if (argv[2])
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
				data->exit_code = 1;
			}
			else
			{
				data->exit_code = ft_atoi(argv[1]) % 256;
				ft_exit(data, data->exit_code);
			}
		}
		else
			bad_exit(data, argv[1]);
	}
	else
	{
		ft_printf("exit\n");
		ft_exit(data, 0);
	}
}
