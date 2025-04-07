/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:15:43 by yishan            #+#    #+#             */
/*   Updated: 2025/04/05 14:32:22 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void	array_clear(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
	arr = NULL;
}

t_bool	print_error_token(t_token *token, t_data *data)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	if (!token->next || token->next == data->token)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token->next->str, 2);
	ft_putstr_fd("'\n", 2);
	return (FALSE);
}
