/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:53:30 by yisho             #+#    #+#             */
/*   Updated: 2025/03/25 16:00:24 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/token.h"

void	token_clear(t_token **token)
{
	t_token	*current;

	if (token && *token)
	{
		current = *token;
		if (current->str)
		{
			free(current->str);
			current->str = NULL;
		}
		token_clear(&(current->next));
		free (current);
		*token = NULL;
	}
}