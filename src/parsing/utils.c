/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:10:44 by yishan            #+#    #+#             */
/*   Updated: 2025/03/25 15:42:24 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

int	ft_is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' \
		|| c == '\t' || c == '\v'))
		return (1);
	return (0);
}

int	ft_is_special(char *str)
{
	if (!str)
		return (0);
	if (str[0] && str[1])
	{
		if (!ft_strncmp(str, "<<", 2))
			return (HEREDOC);
		if (!ft_strncmp(str, ">>", 2))
			return (APPEND);
	}
	if (str[0])
	{
		if (str[0] == '<')
			return (INPUT);
		if (str[0] == '>')
			return (OUTPUT);
		if (str[0] == '|')
			return (PIPE);
	}
	return (0);
}


void	print_error(char *msg)
{
	ft_printf("%s\n", msg);
}

// For debugging
void print_token_list(t_token *head)
{
	while (head->next)
	{
		printf("Type : %d, [%s]\n", head->type, head->str);
		head = head->next;
	}
	printf("Type : %d, [%s]\n", head->type, head->str);
}
