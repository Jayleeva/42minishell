/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:39:04 by yishan            #+#    #+#             */
/*   Updated: 2025/05/13 17:09:56 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void	handle_quotes(char c, t_quote *quote)
{
	if (!quote->double_quote && !quote->single_quote)
	{
		if (c == '\'')
			quote->single_quote = TRUE;
		else if (c == '\"')
			quote->double_quote = TRUE;
		return ;
	}
	else if (quote->double_quote && c == '"')
	{
		quote->double_quote = FALSE;
		return ;
	}
	else if (quote->single_quote && c == '\'')
	{
		quote->single_quote = FALSE;
		return ;
	}
}

int	check_open_quotes(t_data *data, char *input)
{
	int		i;

	data->quote.double_quote = FALSE;
	data->quote.single_quote = FALSE;
	i = 0;
	while (input && input[i])
	{
		handle_quotes(input[i], &data->quote);
		i++;
	}
	if (data->quote.double_quote || data->quote.single_quote)
	{
		ft_putstr_fd("open quote found\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
