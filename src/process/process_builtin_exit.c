/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/15 15:21:43 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../inc/linked_list.h"
#include "../../libft/inc/libft.h"

void	ft_exit(t_data *data, int exit_code)
{
	rl_clear_history();
	//free(data->prompt);
	free_env(&data->env);
	data->exit_code = exit_code;
	token_clear(&data->token);
	cmd_clear(&data->cmd);
	exit(data->exit_code);
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
	ft_exit(data, 2);
}

void	exit_utils(t_data *data, int exit_code)
{
	ft_printf("exit\n");
	ft_exit(data, exit_code);
}

void	process_exit(t_data *data, char **argv)
{
	if (argv[1])
	{
		if (isnum(argv[1]))
		{
			if (argv[2])
			{
				ft_printf("exit\n");
				ft_putstr_fd("minishell: exit: too many arguments\n",
					STDERR_FILENO);
				data->exit_code = 1;
				return ;
			}
			else
			{
				data->exit_code = ft_atoi(argv[1]) % 256;
				exit_utils(data, data->exit_code);
			}
		}
		else
			bad_exit(data, argv[1]);
	}
	exit_utils(data, 0);
}
