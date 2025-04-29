/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:14:02 by yishan            #+#    #+#             */
/*   Updated: 2025/04/29 15:36:49 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

t_bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if (!ft_strncmp("cd", cmd, 3) || \
		!ft_strncmp("echo", cmd, 5) || \
		!ft_strncmp("pwd", cmd, 4) || \
		!ft_strncmp("export", cmd, 7) || \
		!ft_strncmp("unset", cmd, 6) || \
		!ft_strncmp("env", cmd, 3) || \
		!ft_strncmp("exit", cmd, 5))
		return (TRUE);
	return (FALSE);
}
