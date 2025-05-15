/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/15 12:43:39 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void	print_in_output(t_data *data, char *s, int n_flag)
{
	int	temp;

	temp = data->cmd->outfile;
	if (temp == -2)
		temp = 1;
	ft_putstr_fd(s, temp);
	if (!n_flag)
		ft_putchar_fd('\n', temp);
}

char	*echo_utils(char *s, char **argv, int i)
{
	char	*temp;

	while (argv[i])
	{
		temp = s;
		s = ft_strjoin(s, argv[i]);
		free(temp);
		if (argv[i + 1])
		{
			temp = s;
			s = ft_strjoin(s, " ");
			free(temp);
		}
		i ++;
	}
	return (s);
}

void	process_echo(t_data *data, char **argv)
{
	char	*s;
	int		i;
	int		n_flag;

	n_flag = 0;
	s = ft_strdup("");
	data->exit_code = 0;
	i = 1;
	if (argv[1] && !ft_strncmp(argv[1], "-n", 2))
	{
		i = 2;
		n_flag = 1;
	}
	s = echo_utils(s, argv, i);
	print_in_output(data, s, n_flag);
	free(s);
}
