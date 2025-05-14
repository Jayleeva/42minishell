/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:53:30 by yisho             #+#    #+#             */
/*   Updated: 2025/04/14 12:25:02 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linked_list.h"

void	token_clear(t_token **token)
{
	t_token	*current;

	if (token && *token)
	{
		current = *token;
		//write(1, "-A-\n", 4);
		if (current->str)
		{
			//write(1, "-B-\n", 4);
			free(current->str);
			current->str = NULL;
		}
		token_clear(&(current->next));
		free (current);
		*token = NULL;
	}
}
