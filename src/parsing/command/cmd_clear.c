/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:48:24 by yishan            #+#    #+#             */
/*   Updated: 2025/04/02 16:17:19 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linked_list.h"

static void	free_all_cmd(t_cmd *tmp)
{
	if (!tmp)
		return ;

	if (tmp->infile > 0)
		close(tmp->infile);
	tmp->infile = -2;

	if (tmp->outfile > 0)
		close(tmp->outfile);
	tmp->outfile = -2;

	if (tmp->argv)
	{
		array_clear(tmp->argv);
		tmp->argv = NULL;
	}
}

void	cmd_clear(t_cmd **cmd)
{
	t_cmd	*current;

	if (!cmd || !(*cmd))
		return ;
	while (*cmd)
	{
		current = *cmd;
		*cmd = (*cmd)->next;
		free_all_cmd(current);
		free(current);
	}
	*cmd = NULL;
}
