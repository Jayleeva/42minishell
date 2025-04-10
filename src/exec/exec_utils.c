/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:08:02 by yisho             #+#    #+#             */
/*   Updated: 2025/04/10 13:31:40 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void	exit_msg(char *str, int fd, int code)
{
	if (fd == 2)
	{
		ft_putstr_fd("Error: ", fd);
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
		exit (code);
	}
	exit (EXIT_SUCCESS);
}
