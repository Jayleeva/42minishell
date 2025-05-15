/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:53:30 by yisho             #+#    #+#             */
/*   Updated: 2025/05/15 10:44:02 by cyglardo         ###   ########.fr       */
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
